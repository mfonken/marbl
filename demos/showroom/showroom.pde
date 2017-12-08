void setup() {
  size(1000, 700, P3D);
  lights();
  ambientLight(200, 200, 200, 100, 100, 100);
  background(15);
  
  initRoom();
  initBall();
}

void draw() {
  background(15);
  drawRoom();
  drawBall();
  drawFooter();
}