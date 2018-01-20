void getNonGrav()
{
  quaternion_t q = new quaternion_t();
  
  ang3_t r = new ang3_t();
  r.x = RwEst[0];
  r.y = RwEst[1];
  r.z = RwEst[2];
  
  quaternionFromEuler(r, q);
  
  vec3_t l = new vec3_t(), o = new vec3_t();
  l.i = NwEst[0];
  l.j = NwEst[1];
  l.k = NwEst[2];
  
  quaternionRotVec( l, q, o);
  
  FwEst[0] = o.i;
  FwEst[1] = o.j;
  FwEst[2] = o.k;
}


void normalizeValues( )
{
  normalizeAccel();
  normalizeMag();
}

void normalizeAccel()
{
  float n = sqrt( Accel[0] * Accel[0] + Accel[1] * Accel[1] + Accel[2] * Accel[2] );
  Accel[0] /= n;
  Accel[1] /= n;
  Accel[2] /= n;
}

void normalizeMag()
{
  float n = sqrt( Mag[0] * Mag[0] + Mag[1] * Mag[1] + Mag[2] * Mag[2] );
  Mag[0] /= n;
  Mag[1] /= n;
  Mag[2] /= n;
}