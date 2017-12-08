PShape wall1, wall2, floor;
PImage woodImg;
PImage wallImg;
int roomX = 1000;
int roomY = 1000;
int roomZ = 700;

void initRoom() {
  noStroke();
  woodImg = loadImage("dark_wood.jpg");
  wallImg = loadImage("light_wall.jpg");
  wall1 = createShape(RECT, 0, 0, roomX, roomZ);
  wall1.setTexture(wallImg);
  wall2 = createShape(RECT, 0, 0, roomY, roomZ);
  wall2.setTexture(wallImg);
  floor = createShape(RECT, 0, 0, roomX, roomY);
  floor.setTexture(woodImg);
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