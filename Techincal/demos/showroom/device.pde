color device_color = color(85, 85, 85);
int device_radius = 32, device_length = 700;
float point = 1.5;

int ddA = 15, ddB = 15, ddC = 15;
int dL = ( max(ddA, ddB, ddC) + min(ddA, ddB, ddC) ) / 2;
float dsat = 0.4;
float fade_factor = 50;
int dcA = (int)(ddA+(dL-ddA)*dsat), dcB = (int)(ddB+(dL-ddB)*dsat), dcC = (int)(ddC+(dL-ddC)*dsat);


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
    vertex( -point*x, y, x );
  }
  endShape(CLOSE);
  // bottom
  beginShape();
  fill(dcA, dcB, dcC);
  for (int i = 0; i < sides; i++) {
    float x = cos( radians( i * angle ) ) * r;
    float y = sin( radians( i * angle ) ) * r;
    vertex( h, y, x );
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
    fill(x1/r*fade_factor+dcA, x1/r*fade_factor+dcB, x1/r*fade_factor+dcC);
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
  
  float tx = x * UNITS_TO_PIXELS, ty = y * UNITS_TO_PIXELS, tz = z * UNITS_TO_PIXELS;
  
  line(0, 0, 0, tx, 0, 0); 

  stroke(200, 255, 100);
  line(tx, ty, 0, tx, 0, 0); 

  stroke(100, 200, 255);
  line(tx, ty, 0, tx, ty, tz); 
  popMatrix();
}