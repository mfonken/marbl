BufferedReader ratesReader;

char rates_file_id = ' ';
float [] rates_file_values = new float[3];

int iu_rate = 0, tau_rate = 0, com_rate = 0;

void readRatesFile() {
  ratesReader = createReader("/Users/matthewfonken/Desktop/rates.txt"); 
  String line = null;
  try {
    if ((line = ratesReader.readLine()) != null ) {
      //updateState("Connected.");
      String[] values = split(line, ',');
      //print("Reading: ");
      //printA(values);
      if (values.length <= 0 || values[0].length() <= 0) return;
      iu_rate  = int(trim(values[0]));
      tau_rate = int(trim(values[1]));
      com_rate = int(trim(values[2]));
      String rates = ( "IU:" + iu_rate + " T:" + tau_rate + " C:" + com_rate );
      stroke(255);
      textSize(18);
      text(rates + " FPS", width-200, 18);
    }
  } 
  catch(IOException e) {
    updateState("Failed to connect.");
    e.printStackTrace();
  }
}