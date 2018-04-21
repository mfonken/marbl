BufferedReader reader;


char action = ACTION.INACTIVE;
char file_id = ' ';
double [] file_values = new double[10];

double CM_TO_PIXELS = UNITS_TO_PIXELS/100;

double p_n, r_n, w_n, x_n, y_n, z_n;

float ts = 0, nts = 0, fr = 0;

interface ID
{
  char
    NULL_PACKET_ID  = 0xff,
    MESSAGE_ID      = 'm',
    ORIENTATION_ID  = 'o';
};

interface ACTION
{
  char
    INACTIVE    = 0,
    CALIBRATING = 1,
    ACTIVATING  = 2,
    RUNNING     = 3;
};

void readFile() {
  reader = createReader("/Users/matthewfonken/Desktop/out.txt"); 
  String line = null;
  try {
    while ((line = reader.readLine()) != null ) {
      //updateState("Connected.");
      String[] values = split(line, ',');
      //print("Reading: ");
      //printA(values);
      if (values.length <= 0 || values[0].length() <= 0) return;
      file_id = values[0].charAt(0);
      switch( file_id )
      {
        case ID.ORIENTATION_ID:
          updateState("Active.");
          assignFileValues(values);
          break;
        case ID.MESSAGE_ID:
          switch(action)
          {
           case ACTION.CALIBRATING:
             if( values.length < 5 ) return;
             int sc = int(trim(values[1]));
             int ac = int(trim(values[3]));
             int gc = int(trim(values[2]));
             int mc = int(trim(values[4]));

             updateState("SYS-" + sc + " ACC-" + ac + " GYR-" + gc + " MAG-" + mc);
             break;
           case ACTION.ACTIVATING:
             updateState("Activating.");
             break;
           default:
             break;
          }
          action = values[1].charAt(0);
          break;
        default:
          break;
      }
    }
  } 
  catch(IOException e) {
    updateState("Failed to connect.");
    e.printStackTrace();
  }
}

void assignFileValues(String[] values) {
  p_n = float(trim(values[1])) + HALF_PI;
  r_n = float(trim(values[2]));
  w_n = float(trim(values[3]));// - w_offset;
  if(values.length >= 7 )
  {
    x_n = (double)float(trim(values[5])) * CM_TO_PIXELS;
    y_n = (double)float(trim(values[4])) * CM_TO_PIXELS;
    z_n = (double)float(trim(values[6])) * CM_TO_PIXELS;
  }

  p = smooth(p_n, p);
  r = smooth(r_n, r);
  w = smooth(w_n, w);// + QUARTER_PI;
  x = smooth(x_n, x);
  y = smooth(y_n, y);
  z = smooth(z_n, z);

  nts = millis();
  if((nts % 30) == 0 && p != p_n)
  {
    fr = 1000/(nts - ts);
  }
  stroke(255);
  textSize(18);
  text(str(fr).substring(0, 2) + " FPS", 0, 18);
  ts = nts;
}

double smooth(double a, double b) {
  if (Double.isNaN(a)) a = 100;
  if (Double.isNaN(b)) b = 100;
  return (3*b+a)/4;

  //return a;
}

void printA( String[] a) {
  for ( int i = 0; i < a.length; i++ ) print(a[i] + "[" + i + "] ");
  println();
}