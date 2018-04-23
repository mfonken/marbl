String state_string = "Connecting...";

int footer_width = 800;
int footer_height = 130;
int footer_inset = 10;
int inner_inset = 10;
int inner_height = footer_height - 2*(footer_inset+inner_inset);

float rot_dial_start, rot_dial_end;
float rot_dial_length = 0;

int footer_state = 0, footer_delay = 5;

double p_lock, r_lock, w_lock, x_lock, y_lock, z_lock;

/* Color factor defaults */
color text_color = color(245);
int dA = 255, dB = 50, dC = 50;
int L = ( max(dA, dB, dC) + min(dA, dB, dC) ) / 2;
float sat = 0.5;
int cA = (int)(dA+(L-dA)*sat), cB = (int)(dB+(L-dB)*sat), cC = (int)(dC+(L-dC)*sat);

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

void updateState( String s )
{
  state_string = "State: " + s;
}

void drawFooter() {
  fill(15, 15, 15, 127);
  int footer_x = (width-footer_width)/2 + footer_inset;
  stroke(text_color);
  rect(footer_x, height-footer_height+footer_inset, footer_width, footer_height-footer_inset*2);

  stroke(cA, cB, cC);
  drawFooterDial("Pitch", footer_x + (int)lerp(rot_dial_start, rot_dial_end, 0.2), (float)(HALF_PI - p_lock));
  stroke(cC, cA, cB);
  drawFooterDial("Roll", footer_x + (int)lerp(rot_dial_start, rot_dial_end, 0.5), (float)r_lock);
  stroke(cB, cC, cA);
  drawFooterDial("Yaw", footer_x + (int)lerp(rot_dial_start, rot_dial_end, 0.8), (float)(-w_lock+PI));

  stroke(text_color);
  line( footer_x + rot_dial_end, height-footer_height + footer_inset +10, footer_x + rot_dial_end, height-(10 + footer_inset));
  line( footer_x + rot_dial_end + 10, height-footer_height/2-10 + footer_inset, footer_x+footer_width-10, height-footer_height/2 + footer_inset-10);

  drawCoordinateText( (int)(footer_x + rot_dial_end ), (float)(x * PIXELS_TO_UNITS), (float)(y * PIXELS_TO_UNITS), (float)(z * PIXELS_TO_UNITS) );

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
  int footer_center = height-footer_height/2, dial_radius = inner_height/2;
  float tick_length = 2, tick_growth = 0.05, inner_tick = 1-tick_growth, outer_tick = 1+tick_growth;
  int tick_divs = 24;
  textSize(22);
  
  translate(x, footer_center);
  rotate(-HALF_PI);
  ellipse(0, 0, inner_height, inner_height);
  ellipse(0, 0, inner_height/10, inner_height/10);
  line(0, 0, dial_radius*0.8*cos(t), dial_radius*0.8*sin(t));
  
  for(float i = 0; i <= tick_divs; i++ )
  {
    float a = lerp(0, 2*PI, i/tick_divs);
    float inner_radius = dial_radius*inner_tick, outer_radius = dial_radius*outer_tick;
    if( abs((a*180/PI)%90) < 1 ) 
    {
      inner_radius -= tick_length;
      outer_radius += tick_length;
    }
    if( abs((a*180/PI)%30) < 1 ) 
    {
      inner_radius -= tick_length;
      outer_radius += tick_length;
    }
   
    line(inner_radius*cos(a), inner_radius*sin(a), outer_radius*cos(a), outer_radius*sin(a));
  }
  
  fill(text_color);
  text(l, -(dial_radius+6), -(dial_radius+8));
  noFill();
  
  popMatrix();
}

void drawCoordinateText(int text_x, float x_l, float y_l, float z_l) {
  String x_s = str(x_l) + "00000", y_s = str(y_l) + "00000", z_s = str(z_l) + "00000";
  
  int text_width = 270, text_end = text_x+text_width, text_y = height-footer_height/4;
  int digits = 5;
  
  textSize(21);
  fill(cA, cC, cB);
  text(x_s.substring(0, digits), (int)lerp(text_x, text_end, 0.16), text_y);
  fill(cB, cA, cC);
  text(y_s.substring(0, digits), (int)lerp(text_x, text_end, 0.51), text_y);
  fill(cC, cB, cA);
  text(z_s.substring(0, digits), (int)lerp(text_x, text_end, 0.86), text_y);

  fill(text_color);
  text("X:", (int)lerp(text_x, text_end, 0.05), text_y);
  text("Y:", (int)lerp(text_x, text_end, 0.4), text_y);
  text("Z:", (int)lerp(text_x, text_end, 0.75), text_y);
  
  textSize(16*(1+(40/state_string.length())/4));
  text(state_string, text_x+10, height-footer_height*3/4+14);
}