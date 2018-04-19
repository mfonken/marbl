#define DIGITS 3

void txCalibration( uint8_t s, uint8_t a, uint8_t g, uint8_t m )
{
  float packet[4] = { (float)s, (float)a, (float)g, (float)m };
  txMessage( CALIBRATING, packet, 4 );
}

void txAlert( state_action_t action )
{
  float packet[1] = { (float)action };
  txPacket( MESSAGE_ID, packet, 1 );
}

void txMessage( state_action_t action, float * v, int len )
{
  int packet_len = len + 1;
  float packet[packet_len] = { (float)action };
  for(int i = 0; i < len; i++ ) packet[i+1] = v[i];
  txPacket( MESSAGE_ID, packet, packet_len );
}

void txTriplet( packet_id_t id, float a, float b, float c )
{
  float packet[4] = { 3., a, b, c };
  txPacket( id, packet, 4 );
}

void txPacket( packet_id_t id, float * v, int len )
{
 #ifdef ALLOW_PACKET_TX
  Serial.print(" ");
  Serial.print((char)id);
  for( int i = 0; i < len ; i++ )
  {
    Serial.print(",");
    Serial.print(v[i],DIGITS);
  }
  Serial.print("\n");
#endif
}

