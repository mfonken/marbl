int roomX = 1200;
int roomY = 1200;
int roomZ = 700;

boolean live = true;

float [] Accel = new float[3];         //projection of normalized gravitation force vector on x/y/z axis, as measured by accelerometer
float [] Gyro = new float[3];          //Gyro readings
float [] Mag = new float[3];          //Gyro readings
float [] RwGyro = new float[3];        //Rw obtained from last estimated value and gyro movement
float [] Awz = new float[2];           //angles between projection of R on XZ/YZ plane and Z axis (deg)
float [] RwEst = new float[3];
float [] PwEst = new float[3];
float [] NwEst = new float[3];
float [] FwEst = new float[3];
float [] PNwEst = new float[3];
float [] PFwEst = new float[3];

enum OUTPUTS {
  ACCEL, 
    GYRO, 
    MAG, 
    ANG, 
    POS, 
    NON
}

int xPos = 0;