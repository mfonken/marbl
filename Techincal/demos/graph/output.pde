enum OUTPUTS {
  ACCEL, 
    GYRO, 
    MAG, 
    ANG, 
    POS, 
    NON
}

int xPos = 0;

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

void drawGraphs(OUTPUTS o)
{ 
  float scale = 100;
  int gap = 50, xh = 1*((int)scale + gap), yh = 2*((int)scale + gap), zh = 3*((int)scale + gap);
  float x = 0.0, y = 0.0, z = 0.0, a = 0.0, b = 0.0, c = 0.0;

  boolean hasSecondary = false;
  switch (o)
  {
  case ACCEL:
    scale = 100;
    x = Accel[0] * scale;
    y = Accel[1] * scale;
    z = Accel[2] * scale;
    break;
  case GYRO:
    scale = 1;
    x = Gyro[0] * scale;
    y = Gyro[1] * scale;
    z = Gyro[2] * scale;
    break;
  case MAG:
    scale = 15;
    x = Mag[0] * scale;
    y = Mag[1] * scale;
    z = Mag[2] * scale;
    break;
  case ANG:
    scale = 15;
    x = RwEst[0] * scale;
    y = RwEst[1] * scale;
    z = RwEst[2] * scale;
    break;
  case POS:
    scale = 1000;
    x = PwEst[0] * scale;
    y = PwEst[1] * scale;
    z = PwEst[2] * scale;
    break;
  case NON:
    scale = 15;
    x = NwEst[0] * scale;
    y = NwEst[1] * scale;
    z = NwEst[2] * scale;

    scale = 0.5;
    hasSecondary = true;
    a = RwEst[0] * scale;
    b = RwEst[1] * scale;
    c = RwEst[2] * scale;
    break;
  default:
    break;
  }

  //println("xPos is " + xPos + " and x is " + x);

  /* Primary triplet */
  stroke(0, 55, 255);
  line(xPos, xh, xPos, xh - x);
  stroke(0, 127, 127);
  line(xPos, yh, xPos, yh - y);
  stroke(127, 34, 255);
  line(xPos, zh, xPos, zh - z);

  if (hasSecondary)
  {
    /* Secondary triplet */
    stroke(0, 127, 255);
    point(xPos, xh - a);
    stroke(0, 200, 200);
    point(xPos, yh - b);
    stroke(255, 34, 255);
    point(xPos, zh - c);
  }

  if (xPos >= width) {
    background(0);
    xPos = 0;
  } else if (live) {
    xPos++;
  }
  stroke(0);
}

void drawPosition()
{
  println("Non-gravitational acceleration is: X" + NwEst[0] + " Y" + NwEst[1] + " Z" + NwEst[2]);
}

void drawOrientation()
{
  pushMatrix();
  center();
  rotateEuler( RwEst );
  buildBoxShape(5, 5, 100);
  popMatrix();
}

void drawNonGrav()
{
  float scale = 100;
  pushMatrix();
  center();
  stroke(255,100,0);
  
  PNwEst[0] = ( NwEst[0] + PNwEst[0] ) / 2;
  PNwEst[1] = ( NwEst[1] + PNwEst[1] ) / 2;
  PNwEst[2] = ( NwEst[2] + PNwEst[2] ) / 2;
  
  line(0,0,0, PNwEst[0] * scale, PNwEst[1] * scale, PNwEst[2] * scale);
  
  popMatrix();
}


void center()
{
  translate(width/2, height/2, 300);  
}

void rotateEuler( float r[] )
{
  rotateZ(r[0] * DEG_TO_RAD); 
  rotateY(r[1] * DEG_TO_RAD);
  rotateX(r[2] * DEG_TO_RAD);
}

void buildBoxShape(int w, int l, int h) {
  
  
  //box(60, 10, 40);
  noStroke();
  beginShape(QUADS);

  //Z+ (to the drawing area)
  fill(#00ff00);
  vertex(-w, -l, h);
  vertex(w, -l, h);
  vertex(w, l, h);
  vertex(-w, l, h);

  //Z-
  fill(#0000ff);
  vertex(-w, -l, 0);
  vertex(w, -l, 0);
  vertex(w, l, 0);
  vertex(-w, l, 0);

  //X-
  fill(#ff0000);
  vertex(-w, -l, 0);
  vertex(-w, -l, h);
  vertex(-w, l, h);
  vertex(-w, l, 0);

  //X+
  fill(#ffff00);
  vertex(w, -l, 0);
  vertex(w, -l, h);
  vertex(w, l, h);
  vertex(w, l, 0);

  //Y-
  fill(#ff00ff);
  vertex(-w, -l, 0);
  vertex(w, -l, 0);
  vertex(w, -l, h);
  vertex(-w, -l, h);

  //Y+
  fill(#00ffff);
  vertex(-w, l, 0);
  vertex(w, l, 0);
  vertex(w, l, h);
  vertex(-w, l, h);

  endShape();
}