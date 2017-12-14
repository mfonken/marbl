PShape ball;
int ball_radius = 20;
PImage ballImg;

float pos_scale = 30;

float theta;
float x = 0, y = 0, z = 0;
float p = 0, r = 0, w = 0;

void initBall() {
  noStroke();
  ballImg = loadImage("red_orange.jpg");
  ball = createShape(SPHERE, ball_radius); 
  ball.setTexture(ballImg);
}


void drawBall() {
  pushMatrix();
  centerOnBeaconA();
  updateAll();
  //demoAnimation();
  noStroke();
  shape(ball);
  popMatrix();
}