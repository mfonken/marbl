// Graphing sketch

// This program takes ASCII-encoded strings from the serial port at 9600 baud
// and graphs them. It expects values in the range 0 to 1023, followed by a
// newline, or newline and carriage return

// created 20 Apr 2005
// updated 24 Nov 2015
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
String PORT = "/dev/tty.usbmodem1421";
float inByte = 0;

//float [] MAG_CAL = {-0.082, 0.384, 0.087}; // LSM9DS1
float [] MAG_CAL = {-2.396, 38.040, 1.093}; // MPU9250

int lf = '\n';
byte[] inBuffer = new byte[100];

kalman_t pitch,roll,yaw;

void setup () {
  // set the window size:
  size(600, 600, P3D);

  println(Serial.list());

  try {
    String ports[] = Serial.list();
    printArray(ports);
    int i;
    for(i = 0; i < ports.length; i++)
    {
      //println("Checking port #" + i + ": " + ports[i] + " against defined " + PORT);
      if(ports[i].equals(PORT)) 
      {
        myPort = new Serial(this, Serial.list()[i], 115200);
        break;
      }
    }
    if(i == ports.length) throw new Exception();
  }
  catch (Exception e) {
    println("Could not open serial port.");
    exit();
    while (true);
  }
  println("Port opened");
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set initial background:
  background(0);
  initRoom();
}

void draw () {
  readSensors();
  drawRoom();
}


char readSensors() {
  try {
    if (myPort.available() > 0) {
      if (myPort.readBytesUntil(lf, inBuffer) > 0) {
        String inputString = new String(inBuffer);
        String [] inputStringArr = split(inputString, ',');
        //println("Input string: " + inputStringArr.length + "|" + inputString );
        switch(inputStringArr[0].charAt(0))
        {
        case 'r':
          println("Received Raw Data.");
          // convert raw readings to G
          Accel[0] = float(inputStringArr[1]);
          Accel[1] = float(inputStringArr[2]);
          Accel[2] = float(inputStringArr[3]);

          // convert raw readings to degrees/sec
          Gyro[0] = float(inputStringArr[4]);
          Gyro[1] = float(inputStringArr[5]);
          Gyro[2] = float(inputStringArr[6]);

          Mag[1] =  float(inputStringArr[7]) - MAG_CAL[0];
          Mag[0] =  float(inputStringArr[8]) - MAG_CAL[1];
          Mag[2] = -float(inputStringArr[9]) - MAG_CAL[2];

          normalizeValues();
          calculateAngles();
          filterAngles();
          drawGraphs(OUTPUTS.MAG);
          return 'r';
        case 'f':
          println("Received Filtered Data.");
          RwEst[1] = float(inputStringArr[1]);
          RwEst[0] = float(inputStringArr[2]);
          RwEst[2] = float(inputStringArr[3]);

          PwEst[0] = float(inputStringArr[4]);
          PwEst[1] = float(inputStringArr[5]);
          PwEst[2] = float(inputStringArr[6]);

          drawPosition();
          myPort.clear();
          return 'f';
        case 'n':
          //println("Received Non-grav Acceleration Data.");
          RwEst[0] = float(inputStringArr[1]);
          RwEst[1] = float(inputStringArr[2]);
          RwEst[2] = float(inputStringArr[3]);
          
          NwEst[0] = float(inputStringArr[4]);
          NwEst[1] = float(inputStringArr[5]);
          NwEst[2] = float(inputStringArr[6]);
          
          getNonGrav();
          
          RwEst[2] *= -1;
          
          drawOrientation();
          drawNonGrav();
          //drawGraphs(OUTPUTS.NON);
          break;
        case 'w':
          println("Wrote:" + inputStringArr[1] + " " + inputStringArr[2]);
          break;
        default:
          break;
        }
      }
    }
  }
  catch (Exception ex) 
  {
    println("Error!");
  }
  myPort.clear();
  return 'n';
}