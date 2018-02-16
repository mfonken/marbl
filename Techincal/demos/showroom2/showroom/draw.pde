void drawOrientation()
{
  pushMatrix();
  centerInRoom();
  translate(0,0,-200);
  rotateEuler( RwEst );
  buildBoxShape(10, 10, 250);
  popMatrix();
}

void drawNonGrav()
{
  float scale = 250;
  strokeWeight(3);
  
  pushMatrix();
  centerInRoom();
  translate(0,0,-200);
  
  stroke(0,200,255);
  PFwEst[0] = ( FwEst[0] + PFwEst[0] ) / 2;
  PFwEst[1] = ( FwEst[1] + PFwEst[1] ) / 2;
  PFwEst[2] = ( FwEst[2] + PFwEst[2] ) / 2;
  line(0,0,0, PFwEst[0] * scale, PFwEst[1] * scale, PFwEst[2] * scale);
  
  //rotateEuler( RwEst );
  
  stroke(255,100,0);
  PNwEst[0] = ( NwEst[0] + PNwEst[0] ) / 2;
  PNwEst[1] = ( NwEst[1] + PNwEst[1] ) / 2;
  PNwEst[2] = ( NwEst[2] + PNwEst[2] ) / 2; 
  line(0,0,0, PNwEst[0] * scale, PNwEst[1] * scale, PNwEst[2] * scale);
  
  popMatrix();
}

void rotateEuler( float r[] )
{
  rotateZ(r[2]); 
  rotateY(r[1]);
  rotateX(r[0]);
}


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