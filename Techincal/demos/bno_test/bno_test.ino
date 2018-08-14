#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>

#define USE_PARTIAL_CALIBRATION

//#define SERIAL_DEBUG 0
//#define MESSAGE_DEBUG 0
#define ALLOW_PACKET_TX 0

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (1)

Adafruit_BNO055 bno = Adafruit_BNO055(55);
imu::Vector<3> euler;

long reference_time = 0;
#define OFFSET_SAMPLES 10
const byte offset_refresh_button = 4;

typedef enum
{
  NULL_PACKET_ID  = 0xff,
  MESSAGE_ID      = 'm',
  ORIENTATION_ID  = 'o',
  OFFSET_ID       = 'r'
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
  Serial.begin(115200);
  bool restore_cal = false;
  pinMode(offset_refresh_button, INPUT);

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

  //attachInterrupt(digitalPinToInterrupt(offset_refresh_button), sendOffset, FALLING);

  delay(500);
  txAlert( RUNNING );
  reference_time = millis();
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop( void )
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2

  /*
    if( ( millis() - reference_time ) > 5000 )
    {
    sendOffset();
    reference_time = millis();
    }
  */
  
  if ( Serial.available() > 0 )
  {
    switch ( Serial.read() )
    {
      case 'c':
        delay(10);
        sendOffset();
        delay(500);
        break;
      case 'o':
        euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        //  imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
        txTriplet( ORIENTATION_ID, euler.x(), euler.y(), euler.z() );
        delay(BNO055_SAMPLERATE_DELAY_MS);
      default:
        break;
    }
    Serial.flush();
  }
  
}

void sendOffset( void )
{
  imu::Vector<3> euler;
  float samples[3] = {  0., 0., 0. };
  for ( int i = OFFSET_SAMPLES; i > 0; --i )
  {
    euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    samples[0] += euler.x();
    samples[1] += euler.y();
    samples[2] += euler.z();
  }
  samples[0] /= OFFSET_SAMPLES;
  samples[1] /= OFFSET_SAMPLES;
  samples[2] /= OFFSET_SAMPLES;
  txTriplet( OFFSET_ID, samples[0], samples[1], samples[2] );
}

