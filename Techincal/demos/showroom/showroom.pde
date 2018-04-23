int roomX = 1200;
int roomY = 1200;
int roomZ = 700;

void setup() {
  size(1000, 700, P3D);
  lights();
  ambientLight(200, 200, 200, 100, 100, 100);
  background(15);
  
  initGeneral();
  initFooter();
  initRoom();
  initBall();
  initDevice();
  initBeacons();
  
}

void draw() {
  background(backgroundImg);
  drawRoom();
  readFile();
  drawFooter();
  drawBeacons();
  
  drawBall();
  drawDevice();
}