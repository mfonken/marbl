boolean locked = false;
float ROTATION_SENSITIVITY = 0.001;
int x_mouse_lock = 0, y_mouse_lock = 0;

float [] rot_pre = { PI*5/13, 0, PI/4 };
float [] rot = { PI*5/13, 0, PI/4 };

int state = 0;
int max_state = 1000;

float p_angle_start = 0, p_angle_end = 60;
float p_inc = (p_angle_end - p_angle_start) * PI/180 * 2;
float r_angle_start = -45, r_angle_end = 45;
float r_inc = (r_angle_end - r_angle_start) * PI/180 * 2;
float w_angle_start = -45, w_angle_end = 45;
float w_inc = (w_angle_end - w_angle_start) * PI/180 * 2;

float w_offset = 0;

void initGeneral() {
  RwEst[0] = p_angle_start * PI/180;
  RwEst[1] = r_angle_start * PI/180;
  RwEst[2] = w_angle_start * PI/180;
  
  textSize(36);
}


void center() {
  translate(width/2, (height-footer_height)*4/13, -1500);
  rotateX(rot[0]);
  rotateZ(rot[2]);
}

void keyReleased() {
  if (key == ' ') {
    w_offset = RwEst[0];
    println("Yaw Offset is " + w_offset);
  }
}

void mousePressed() {
  locked = true;
  x_mouse_lock = mouseX;
  y_mouse_lock = mouseY;
}

void mouseDragged() {
  if (locked) {
    float x_diff = (float)(mouseX - x_mouse_lock);
    float y_diff = (float)(mouseY - y_mouse_lock);
    rot[2] = rot_pre[2] + x_diff*ROTATION_SENSITIVITY; 
    rot[0] = rot_pre[0] + y_diff*ROTATION_SENSITIVITY;

    stroke(245);
    line(x_mouse_lock, y_mouse_lock, mouseX, mouseY);
  }
}

void mouseReleased() {
  locked = false;
  rot_pre[0] = rot[0];
  rot_pre[1] = rot[1];
  rot_pre[2] = rot[2];
}