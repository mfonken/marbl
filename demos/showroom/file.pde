BufferedReader reader;

char file_id = ' ';
double [] file_values = new double[10];

float CM_TO_PIXELS = UNITS_TO_PIXELS/100;

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
  p = float(trim(values[1])) + HALF_PI;
  r = float(trim(values[2]));
  w = float(trim(values[3]));

  x = float(trim(values[5]));
  y = float(trim(values[4]));
  z = float(trim(values[6]));
  
  x *= CM_TO_PIXELS;
  y *= CM_TO_PIXELS;
  z *= CM_TO_PIXELS;
  
  x += Ax;
  y += Ay;
  z += Az;
}

void printA( String[] a) {
  for ( int i = 0; i < a.length; i++ ) print(a[i] + "[" + i + "] ");
  println();
}