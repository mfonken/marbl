boolean demo_p = true, demo_r = true, demo_w = true;

void demoAnimation() {
  float radius = 300, bounce = 100, speed = 1;
  theta = ((float)state/(float)max_state * 2 * PI) * speed;
  x = radius * cos(theta);
  y = radius * sin(theta);
  z = bounce * cos(theta) + roomZ/2;
  
  boolean dir;
  dir = (state < max_state/2);
  if(demo_p) p += p_inc/(float)max_state * (dir?1:-1);
  if(demo_r) r += r_inc/(float)max_state * (dir?1:-1);
  if(demo_w) w += w_inc/(float)max_state * (dir?1:-1);
  
  if (++state >= max_state) state = 0;
}