BufferedReader reader;

char file_id = ' ';
double [] file_values = new double[10];

float CM_TO_PIXELS = UNITS_TO_PIXELS/100;

float p_n, r_n, w_n, x_n, y_n, z_n;

void readFile() {
  reader = createReader("/Users/matthewfonken/Desktop/out.txt"); 
  String line = null;
  try {
    while ((line = reader.readLine()) != null ) {
      String[] values = split(line, ',');
      //print("Reading: ");
      //printA(values);
      if (values.length <= 0 || values[0].length() <= 0) return;
      file_id = values[0].charAt(0);
      if (file_id == 'f') {
        assignFileValues(values);
      }
    }
  } 
  catch(IOException e) {
    e.printStackTrace();
  }
}

void assignFileValues(String[] values) {
  p_n = float(trim(values[1])) + HALF_PI;
  r_n = float(trim(values[2]));
  w_n = float(trim(values[3]));// - w_offset;

  x_n = float(trim(values[5]));
  y_n = float(trim(values[4]));
  z_n = float(trim(values[6]));

  x_n *= CM_TO_PIXELS;
  y_n *= CM_TO_PIXELS;
  z_n *= CM_TO_PIXELS;

  p = smooth(p_n, p);
  r = smooth(r_n, r);
  w = smooth(w_n, w);// + QUARTER_PI;
  x = smooth(x_n, x);
  y = smooth(y_n, y);
  z = smooth(z_n, z);
}

float smooth(float a, float b) {
  if(Float.isNaN(a)) a = 100;
  if(Float.isNaN(b)) b = 100;
  return a;//(a+b)/2;
}

void printA( String[] a) {
  for ( int i = 0; i < a.length; i++ ) print(a[i] + "[" + i + "] ");
  println();
}