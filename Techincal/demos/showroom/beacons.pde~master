PShape beaconA, beaconB;
int beacon_radius = 20;
color beacon_color = color(255, 0, 0);//, 55);
PImage beaconImg;

color case_color = color(155, 150, 155);
int case_radius = 30, case_height = 60;

float UNITS_TO_PIXELS = 3;
float PIXELS_TO_UNITS = 1/ UNITS_TO_PIXELS;
float beacons_distance_UNITS = 57;
int beacons_distance = 0;
int beacons_x = roomX/4, beacons_y = roomY/2;
int Ax, Ay, Az, Bx, By;

void initBeacons() {
  noStroke();
  beaconImg = loadImage("red_orange.jpg");
  beaconA = createShape(SPHERE, beacon_radius); 
  beaconB = createShape(SPHERE, beacon_radius); 
  beaconA.setTexture(beaconImg);
  beaconB.setTexture(beaconImg);

  beacons_distance = (int)(beacons_distance_UNITS * UNITS_TO_PIXELS);
  Ax = beacons_x + beacon_radius;
  Ay = beacons_y + beacon_radius - (int)(beacons_distance/2);
  Az = (int)((float)beacon_radius*2.75);
  Bx = Ax;
  By = Ay + beacons_distance;
}

void drawBeacons() {
  pushMatrix();
  center();
  translate(Ax, Ay, case_height/2);
  drawCase(10, case_radius, beacons_distance, case_height);
  translate(0, 0, Az - case_height/2);
  rotateZ(PI);
  shape(beaconA);
  rotateZ(-PI);
  translate(Bx-Ax, By-Ay, 0);
  rotateZ(PI);
  shape(beaconB);
  rotateZ(-PI);
  popMatrix();
}

void drawCase( int sides, float r, int w, float h)
{
  stroke(15);
  fill(case_color);
  pushMatrix();
  float angle = -180 / sides;
  float halfHeight = h / 2;
  float x1, y1, x2, y2, ra;
  noStroke();
  fill(case_color);

  stroke(15);
  // Right Bottom Semi
  beginShape();
  for (int i = 0; i < sides; i++) {
    ra = radians( i * angle );
    x1 = cos( ra ) * r;
    y1 = sin( ra ) * r;
    vertex( x1, y1, -halfHeight);
  }
  endShape();

  // Right Top Semi
  beginShape();
  for (int i = 0; i < sides; i++) {
    ra = radians( i * angle );
    x2 = cos( ra ) * r;
    y2 = sin( ra ) * r;
    vertex( x2, y2, halfHeight);
  }
  endShape(CLOSE);

  noStroke();
  // Right Shell
  beginShape(TRIANGLE_STRIP);
  for (int i = 0; i < sides + 1; i++) {
    ra = radians( i * angle );
    x1 = cos( ra ) * r;
    y1 = sin( ra ) * r;
    vertex( x1, y1, -halfHeight);
    vertex( x1, y1, halfHeight);
  }
  endShape(CLOSE);
 
  stroke(15);
  translate(0, w/2, 0);
  box(r*2,w,h);
  translate(0, w/2, 0);

  // Left Bottom Semi
  beginShape();
  for (int i = 0; i < sides; i++) {
    ra = radians( i * -angle );
    x1 = cos( ra ) * r;
    y1 = sin( ra ) * r;
    vertex( x1, y1, -halfHeight);
  }
  endShape(CLOSE);
  
  // Left Top Semi
  beginShape();
  for (int i = 0; i < sides; i++) {
    ra = radians( i * -angle );
    x1 = cos( ra ) * r;
    y1 = sin( ra ) * r;
    vertex( x1, y1, halfHeight);
  }
  endShape(CLOSE);
  
  noStroke();
  //Left Shell
  beginShape(TRIANGLE_STRIP);
  for (int i = 0; i < sides + 1; i++) {
    ra = radians( i * -angle );
    x2 = cos( ra ) * r;
    y2 = sin( ra ) * r;
    vertex( x2, y2, -halfHeight);
    vertex( x2, y2, halfHeight);
  }
  endShape(CLOSE);

  popMatrix();
} 