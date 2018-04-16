int footer_width = 800;
int footer_height = 130;
int footer_inset = 10;
int inner_inset = 10;
int inner_height = footer_height - 2*(footer_inset+inner_inset);

float rot_dial_start, rot_dial_end;
float rot_dial_length = 0;

int footer_state = 0, footer_delay = 5;

double p_lock, r_lock, w_lock, x_lock, y_lock, z_lock;

void initFooter() {
  footer_state = 0;
  rot_dial_start = (float)footer_width * 0;
  rot_dial_end   = (float)footer_width * 5/8;
  p_lock = p;
  r_lock = r;
  w_lock = w;
  x_lock = x;
  y_lock = y;
  z_lock = z;
}

void drawFooter() {
  fill(15, 15, 15, 127);
  int footer_x = (width-footer_width)/2 + footer_inset;
  stroke(245);
  rect(footer_x, height-footer_height+footer_inset, footer_width, footer_height-footer_inset*2);

  stroke(255, 200, 100);
  drawFooterDial("Pitch", footer_x + (int)lerp(rot_dial_start, rot_dial_end, 0.2), (float)(HALF_PI - p_lock));
  stroke(100, 255, 200);
  drawFooterDial("Roll", footer_x + (int)lerp(rot_dial_start, rot_dial_end, 0.5), (float)r_lock);
  stroke(200, 100, 255);
  drawFooterDial("Yaw", footer_x + (int)lerp(rot_dial_start, rot_dial_end, 0.8), (float)(-w_lock+PI));

  stroke(245);
  line( footer_x + rot_dial_end, height-footer_height + footer_inset +10, footer_x + rot_dial_end, height-(10 + footer_inset));

  drawCoordinateText( (int)(footer_x + rot_dial_end + 4 ), (float)(x * PIXELS_TO_UNITS), (float)(y * PIXELS_TO_UNITS), (float)(z * PIXELS_TO_UNITS) );

  if (footer_state <= footer_delay)
  {
    footer_state++;
    return;
  }
  footer_state = 0;
  p_lock = p;
  r_lock = r;
  w_lock = w;
  x_lock = x;
  y_lock = y;
  z_lock = z;
}

void drawFooterDial(String l, int x, float t) {
  pushMatrix();
  textSize(22);
  int footer_center = height-footer_height/2, dial_radius = inner_height/2;
  translate(x, footer_center);
  rotate(-HALF_PI);
  ellipse(0, 0, inner_height, inner_height);
  line(0, 0, dial_radius*0.8*cos(t), dial_radius*0.8*sin(t));
  fill(245);
  ellipse(0, 0, 5, 5);
  text(l, -dial_radius, -(dial_radius+4));//dial_radius, -dial_radius);
  noFill();
  popMatrix();
}

void drawCoordinateText(int text_x, float x_l, float y_l, float z_l) {
  String x_s = str(x_l) + "00000", y_s = str(y_l) + "00000", z_s = str(z_l) + "00000";
  
  int text_width = 270, text_end = text_x+text_width+6, text_y = height-footer_height/2+6;
  int digits = 6;
  
  textSize(22);
  fill(255, 100, 200);
  text(x_s.substring(0, digits), (int)lerp(text_x, text_end, 0.05), text_y);
  fill(255);
  text(",", (int)lerp(text_x, text_end, 0.35), text_y);
  fill(200, 255, 100);
  text(y_s.substring(0, digits), (int)lerp(text_x, text_end, 0.4), text_y);
  fill(255);
  text(",", (int)lerp(text_x, text_end, 0.7), text_y);
  fill(100, 200, 255);
  text(z_s.substring(0, digits), (int)lerp(text_x, text_end, 0.75), text_y);

  textSize(32);
  fill(255);
  text("(", text_x+6, text_y+2);
  text(")", text_end+2, text_y+2);
  
  text("X", (int)lerp(text_x, text_end, 0.16), text_y+32);
  text("Y", (int)lerp(text_x, text_end, 0.52), text_y+32);
  text("Z", (int)lerp(text_x, text_end, 0.86), text_y+32);
}