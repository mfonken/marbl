int roomX = 1200;
int roomY = 1200;
int roomZ = 700;

PShape wall1, wall2, floor;
PImage woodImg;
PImage wall1Img, wall2Img;

void initRoom() {
  noStroke();
  woodImg = loadImage("dark_wood.jpg");
  wall1Img = loadImage("concrete_a.jpg");
  wall2Img = loadImage("concrete_a.jpg");
  wall1 = createShape(RECT, 0, 0, roomX, roomZ);
  wall1.setTexture(wall1Img);
  wall2 = createShape(RECT, 0, 0, roomY, roomZ);
  wall2.setTexture(wall2Img);
  floor = createShape(RECT, 0, 0, roomX, roomY);
  floor.setTexture(woodImg);
}

void centerInRoom() {
  center();
  translate(roomX/2, roomY/2, roomZ/2);
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