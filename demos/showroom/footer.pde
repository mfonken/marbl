int footer_width = 500;
int footer_height = 130;
int footer_inset = 10;
int inner_inset = 10;
int inner_height = footer_height - 2*(footer_inset+inner_inset);

void drawFooter() {
  int footer_x = (width-footer_width)/2 + footer_inset;
  stroke(245);
  noFill();
  rect(footer_x, height-footer_height+footer_inset, footer_width, footer_height-footer_inset*2);
  drawFooterDial(footer_width/6+footer_x, p);
  drawFooterDial(footer_width/2+footer_x, r);
  drawFooterDial(footer_width*5/6+footer_x, w);
}

void drawFooterDial(int x, float t) {
  int footer_center = height-footer_height/2, dial_radius = inner_height/2;
  ellipse(x, footer_center, inner_height, inner_height);
  line(x, footer_center, x+dial_radius*cos(t), footer_center+dial_radius*sin(t));
}