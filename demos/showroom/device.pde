color device_color = color(80, 85, 80);
int device_radius = 25, device_length = 500;
float point = 1.5;

void initDevice() {
}

void drawDevice() {
  pushMatrix();
  centerOnBeaconA();
  //demoAnimation();
  updateAll();
  noStroke();
  fill(device_color);
  drawStylus(10, device_radius, device_length);
  popMatrix();
  drawCoordinateLines();
}

void drawStylus( int sides, float r, float h)
{
  stroke(15);
  float angle = 360 / sides;
  // top
  beginShape();
  for (int i = 0; i < sides; i++) {
    float x = cos( radians( i * angle ) ) * r;
    float y = sin( radians( i * angle ) ) * r;
    vertex( -point*x, y, x);
  }
  endShape(CLOSE);
  // bottom
  beginShape();
  fill(200, 205, 255);
  for (int i = 0; i < sides; i++) {
    float x = cos( radians( i * angle ) ) * r;
    float y = sin( radians( i * angle ) ) * r;
    vertex( h, y, x);
  }
  endShape(CLOSE);
  // draw body
  noStroke();
  beginShape(TRIANGLE_STRIP);
  for (int i = 0; i < sides + 1; i++) {
    float x1 = cos( radians( i * angle ) ) * r;
    float y1 = sin( radians( i * angle ) ) * r;
    float x2 = cos( radians( i * angle ) ) * r;
    float y2 = sin( radians( i * angle ) ) * r;
    fill(x1/r*50+130, x1/r*50+150, x1/r*55+200);
    vertex( -point*x1, y1, x1);
    vertex( h, y2, x2);
  }
  endShape(CLOSE);
} 

void drawCoordinateLines() {
  pushMatrix();
  center();
  translate(Ax, Ay, Az);
  stroke(255, 100, 200);
  line(0, 0, 0, x, 0, 0); 

  stroke(200, 255, 100);
  line(x, y, 0, x, 0, 0); 

  stroke(100, 200, 255);
  line(x, y, 0, x, y, z); 
  popMatrix();
}