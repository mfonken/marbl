void buildBoxShape(int w, int l, int h) {
  //box(60, 10, 40);
  noStroke();
  beginShape(QUADS);

  //Z+ (to the drawing area)
  fill(#00ff00);
  vertex(-w, -l, h);
  vertex(w, -l, h);
  vertex(w, l, h);
  vertex(-w, l, h);

  //Z-
  fill(#0000ff);
  vertex(-w, -l, 0);
  vertex(w, -l, 0);
  vertex(w, l, 0);
  vertex(-w, l, 0);

  //X-
  fill(#ff0000);
  vertex(-w, -l, 0);
  vertex(-w, -l, h);
  vertex(-w, l, h);
  vertex(-w, l, 0);

  //X+
  fill(#ffff00);
  vertex(w, -l, 0);
  vertex(w, -l, h);
  vertex(w, l, h);
  vertex(w, l, 0);

  //Y-
  fill(#ff00ff);
  vertex(-w, -l, 0);
  vertex(w, -l, 0);
  vertex(w, -l, h);
  vertex(-w, -l, h);

  //Y+
  fill(#00ffff);
  vertex(-w, l, 0);
  vertex(w, l, 0);
  vertex(w, l, h);
  vertex(-w, l, h);

  endShape();
}