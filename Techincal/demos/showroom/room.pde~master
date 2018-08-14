PShape wall1, wall2, floor;
PImage woodImg;
PImage wall1Img, wall2Img;
PImage backgroundImg;

void initRoom() {
  noStroke();
  woodImg = loadImage("concrete_b.jpg");
  wall1Img = loadImage("lightened_dark_wood.jpg");
  wall2Img = loadImage("lightened_dark_wood.jpg");
  wall1 = createShape(RECT, 0, 0, roomX, roomZ);
  wall1.setTexture(wall1Img);
  wall2 = createShape(RECT, 0, 0, roomY, roomZ);
  wall2.setTexture(wall2Img);
  floor = createShape(RECT, 0, 0, roomX, roomY);
  floor.setTexture(woodImg);
  
  backgroundImg = loadImage("dark_triangles_1000_700.jpg");
}

void centerInRoom() {
  center();
  translate(roomX/2, roomY/2, roomZ/2);
}

void centerOnBeaconA() {
  center();
  translate(Ax, Ay, Az);
}

void drawRoom() {
  pushMatrix();
  center();

  noStroke();
  fill(255, 245, 245);

  shape(floor);

  rotateX(PI/2);
  shape(wall2);

  rotateX(-PI/2);
  rotateZ(PI/2);
  rotateX(PI/2);
  shape(wall1);

  popMatrix();
}