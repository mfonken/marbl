import processing.serial.*;

Serial myPort;        // The serial port
String PORT = "/dev/tty.usbmodem1421";
float inByte = 0;
int lf = '\n';
byte[] inBuffer = new byte[100];

float [] MAG_CAL = {-2.396, 38.040, 1.093}; // MPU9250

void initSerial()
{
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
}

char readSerial() {
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
          //calculateAngles();
          //filterAngles();
          drawGraphs(OUTPUTS.MAG);
          return 'r';
        case 'f':
          println("Received Filtered Data.");
          RwEst[1] = float(inputStringArr[1]) * DEG_TO_RAD;
          RwEst[0] = float(inputStringArr[2]) * DEG_TO_RAD;
          RwEst[2] = float(inputStringArr[3]) * DEG_TO_RAD;

          PwEst[0] = float(inputStringArr[4]);
          PwEst[1] = float(inputStringArr[5]);
          PwEst[2] = float(inputStringArr[6]);

          myPort.clear();
          return 'f';
        case 'n':
          //println("Received Non-grav Acceleration Data.");
          RwEst[0] = float(inputStringArr[1]) * DEG_TO_RAD; //pitch
          RwEst[1] = float(inputStringArr[2]) * DEG_TO_RAD; //roll
          RwEst[2] = float(inputStringArr[3]) * DEG_TO_RAD; //yaw
          
          NwEst[0] = float(inputStringArr[4]);
          NwEst[1] = float(inputStringArr[5]);
          NwEst[2] = float(inputStringArr[6]);
          
          getNonGrav();
          updateBall(NwEst);
         
          background(15);
          drawRoom();
          drawOrientation();
          drawNonGrav();
          drawBall();
          
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
    //println("Error!");
  }
  myPort.clear();
  return 'n';
}