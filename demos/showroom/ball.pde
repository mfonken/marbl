PShape ball;
int ball_radius = 100;
PImage ballImg;

float theta;
float x = 0, y = 0, z = 0;
float p = 0, r = 0, w = 0;

void initBall() {
  noStroke();
  ballImg = loadImage("red_bumps.jpg");
  ball = createShape(SPHERE, ball_radius); 
  ball.setTexture(ballImg);
}


void drawBall() {
  float radius = 300, bounce = 100, speed = 4;
  theta = ((float)state/(float)max_state * 2 * PI) * speed;
  x = radius * cos(theta);
  y = radius * sin(theta);
  z = bounce * cos(theta);

  p = theta / 2;
  r = theta / 4;
  w = theta / 3;

  pushMatrix();
  center();
  noStroke();
  translate(roomX/2, roomY/2, roomZ/2);
  translate(x, y, z);
  rotateX(p);
  rotateY(r);
  rotateZ(w);
  shape(ball);
  popMatrix();

  if (++state >= max_state) state = 0;
}