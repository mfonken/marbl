boolean locked = false;
float ROTATION_SENSITIVITY = 0.001;
int x_lock = 0, y_lock = 0;

float [] rot_pre = { PI*5/13, 0, PI/4 };
float [] rot = { PI*5/13, 0, PI/4 };

int state = 0;
int max_state = 1000;

void center() {
  translate(width/2, (height-footer_height)*4/13, -1500);
  rotateX(rot[0]);
  rotateZ(rot[2]);
}

void mousePressed() {
  locked = true;
  x_lock = mouseX;
  y_lock = mouseY;
}

void mouseDragged() {
  if (locked) {
    float x_diff = (float)(mouseX - x_lock);
    float y_diff = (float)(mouseY - y_lock);
    rot[2] = rot_pre[2] + x_diff*ROTATION_SENSITIVITY; 
    rot[0] = rot_pre[0] + y_diff*ROTATION_SENSITIVITY;

    stroke(245);
    line(x_lock, y_lock, mouseX, mouseY);
  }
}

void mouseReleased() {
  locked = false;
  rot_pre[0] = rot[0];
  rot_pre[1] = rot[1];
  rot_pre[2] = rot[2];
}