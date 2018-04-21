#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>

//#define SERIAL_DEBUG 0
//#define MESSAGE_DEBUG 0
#define ALLOW_PACKET_TX 0

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

typedef enum
{
  NULL_PACKET_ID  = 0xff,
  MESSAGE_ID      = 'm',
  ORIENTATION_ID  = 'o'
} packet_id_t;

typedef enum
{
  CALIBRATING = 1,
  ACTIVATING,
  RUNNING
} state_action_t;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(9600);
  bool restore_cal = false;

  while (Serial.available() <= 0);
  switch (Serial.read())
  {
    case 'r':
      restore_cal = true;
      break;
    default:
      break;
  }
  Serial.flush();
#ifdef MESSAGE_DEBUG
#else
  delay(2000);
#endif

#ifdef MESSAGE_DEBUG
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
#endif

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
#ifdef MESSAGE_DEBUG
    Serial.print("No BNO055 detected ... Check your wiring or I2C ADDR!");
#endif
    while (1);
  }

  /* Set BNO Config to P0 */
  writeReg8(0x41, 0x21); // P0
  delay(10);
  writeReg8(0x42, 0x04); // P0
  delay(10);

  int eeAddress = 0;
  long bnoID;
  sensor_t sensor;
  
  if ( restore_cal ) {
    EEPROM.get(eeAddress, bnoID);

    adafruit_bno055_offsets_t calibrationData;

    /*
       Look for the sensor's unique ID at the beginning oF EEPROM.
       This isn't foolproof, but it's better than nothing.
    */
    bno.getSensor(&sensor);
    if (bnoID != sensor.sensor_id)
    {
#ifdef MESSAGE_DEBUG
      Serial.println("\nNo Calibration Data for this sensor exists in EEPROM");
#endif
      delay(500);
    }
    else
    {
#ifdef MESSAGE_DEBUG
      Serial.println("\nFound Calibration for this sensor in EEPROM.");
#endif
      eeAddress += sizeof(long);
      EEPROM.get(eeAddress, calibrationData);

#ifdef MESSAGE_DEBUG
      displaySensorOffsets(calibrationData);
#endif
      Serial.println("\n\nRestoring Calibration data to the BNO055...");
      bno.setSensorOffsets(calibrationData);

      Serial.println("\n\nCalibration data loaded into BNO055");
    }

    delay(1000);
  }

#ifdef MESSAGE_DEBUG
  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();
#endif

  bno.setExtCrystalUse(true);

  sensors_event_t event;
  bno.getEvent(&event);
  if ( restore_cal ) {
#ifdef MESSAGE_DEBUG
    Serial.println("Move sensor slightly to calibrate magnetometers");
#endif
    while (!bno.isFullyCalibrated())
    {
      bno.getEvent(&event);
      delay(BNO055_SAMPLERATE_DELAY_MS);
    }
  }
  else
  {
#ifdef MESSAGE_DEBUG
    Serial.println("Please Calibrate Sensor: ");
#endif
    while (!isPartiallyCalibrated())//bno.isFullyCalibrated())
    {
      bno.getEvent(&event);
#ifdef SERIAL_DEBUG
      Serial.print("X: ");
      Serial.print(event.orientation.x, 4);
      Serial.print("\tY: ");
      Serial.print(event.orientation.y, 4);
      Serial.print("\tZ: ");
      Serial.print(event.orientation.z, 4);
      Serial.println("");
#endif

      /* Optional: Display calibration status */
      displayCalStatus();

      /* Wait the specified delay before requesting new data */
      delay(BNO055_SAMPLERATE_DELAY_MS);
    }
  }
  txAlert( ACTIVATING );
#ifdef MESSAGE_DEBUG
  Serial.println("\nFully calibrated!");
  Serial.println("--------------------------------");
  Serial.println("Calibration Results: ");
#endif

  
  adafruit_bno055_offsets_t newCalib;
  bno.getSensorOffsets(newCalib);
#ifdef MESSAGE_DEBUG
  displaySensorOffsets(newCalib);
  Serial.println("\n\nStoring calibration data to EEPROM...");
#endif
  eeAddress = 0;
  bno.getSensor(&sensor);
  bnoID = sensor.sensor_id;

  EEPROM.put(eeAddress, bnoID);

  eeAddress += sizeof(long);
  EEPROM.put(eeAddress, newCalib);
#ifdef SERIAL_DEBUG
  Serial.println("Data stored to EEPROM.");

  Serial.println("\n--------------------------------\n");
#endif
  delay(500);
  txAlert( RUNNING );
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2

  imu::Vector<3> euler  = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  //  imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

  txTriplet( ORIENTATION_ID, euler.x(), euler.y(), euler.z() );
  //  txAlert( ACTIVATING );
  delay(BNO055_SAMPLERATE_DELAY_MS);
}




