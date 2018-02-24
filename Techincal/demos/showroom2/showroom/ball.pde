PShape ball;
int ball_radius = 20;
PImage ballImg;

kalman_t bx, by, bz;

float bv[] = {0,0,0};

float ts;

void initBall() {
  noStroke();
  
  bx = new kalman_t();
  by = new kalman_t();
  bz = new kalman_t();
  
  ballImg = loadImage("red_orange.jpg");
  ball = createShape(SPHERE, ball_radius); 
  ball.setTexture(ballImg);
  ts = millis()/1000;
}

void updateBall( float a[] )
{ 
  float px, py, pz;
  px = a[0] * (ts*ts) + bv[0] * ts;// + bx.value;
  py = a[1] * (ts*ts) + bv[1] * ts;// + by.value;
  pz = a[2] * (ts*ts) + bv[2] * ts;// + bz.value;
  
  bx.update( px, a[0] );
  by.update( py, a[1] );
  bz.update( pz, a[2] );
  
  bv[0] = a[0] * ts;
  bv[1] = a[1] * ts;
  bv[2] = a[2] * ts;
  
  ts = millis()/1000;
}

void drawBall() {
  float scale = 10, x, y, z;
  x = bx.value/scale;
  y = by.value/scale;
  z = bz.value/scale;
  
  pushMatrix();
  centerInRoom();
  rotateZ(RwEst[2]);
  translate(-x, y, z);
  noStroke();
  shape(ball);
  popMatrix();
}