class ang3_t
{
  float    x;                /**< Phi value */
  float    y;                /**< Theta value */
  float    z;                /**< Psi value */
} 

/*! Quaternion hypercomplex type */
class quaternion_t
{
  float x;
  float y;
  float z;
  float w;
};

/* See - http://www.gamasutra.com/view/feature/131686/rotating_objects_using_quaternions.php */
/* Generic intrinsic euler angles to quaternion conversion */
void quaternionFromEuler( ang3_t a, quaternion_t q )
{
  float half_roll, half_pitch, half_yaw;
  half_roll   = a.x / 2;
  half_pitch  = a.y / 2;
  half_yaw    = a.z / 2;
  float cr, cp, cy, sr, sp, sy, cpcy, spsy, spcy, cpsy;
  cr = cos( half_roll  );
  cp = cos( half_pitch );
  cy = cos( half_yaw   );
  sr = sin( half_roll  );
  sp = sin( half_pitch );
  sy = sin( half_yaw   );
  cpcy = cp * cy;
  spsy = sp * sy;
  spcy = sp * cy;
  cpsy = cp * sy;
  q.w = cr * cpcy + sr * spsy;
  q.x = sr * cpcy - cr * spsy;
  q.y = cr * spcy + sr * cpsy;
  q.z = cr * cpsy - sr * spcy;
}

void quaternionToEuler( quaternion_t q, ang3_t a )
{
  float w = q.w, x = q.x, y = q.y, z = q.z, m, n;

  m = 2*(w*x+y*z);
  n = 1-2*(x*x+y*y);
  a.x = atan2(m, n);

  m = 2*(w*y-x*z);
  a.y = asin(m);

  m = 2*(w*z+x*y);
  n = 1-2*(y*y+z*z);
  a.z = atan2(m, n);
}

/* See - https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/ */
void quaternionRotVec(vec3_t v, quaternion_t q, vec3_t r)
{
  vec3_t u = new vec3_t();
  u.i = q.x;
  u.j = q.y;
  u.k = q.z;
  float s = q.w;
  vec3_t a = new vec3_t(), b = new vec3_t(), c = new vec3_t(), t = new vec3_t();

  mul3  (  2, u, a );
  cross3( a, v, t );
  cross3( u, t, b );
  mul3  (  s, t, c );
  add33 (  v, b, c, r );
}

/* float quaternion Hamilton multiplication (Generic) */
void quaternionCombine(quaternion_t a, quaternion_t b, quaternion_t c )
{
  float A, B, C, D, E, F, G, H;
  A = ( a.w + a.x ) * ( b.w + b.x );
  B = ( a.z - a.y ) * ( b.y - b.z );
  C = ( a.w - a.x ) * ( b.y + b.z );
  D = ( a.y + a.z ) * ( b.w - b.x );
  E = ( a.x + a.z ) * ( b.x + b.y );
  F = ( a.x - a.z ) * ( b.x - b.y );
  G = ( a.w + a.y ) * ( b.w - b.z );
  H = ( a.w - a.y ) * ( b.w + b.z );
  c.w = B + ( -E - F + G + H ) / 2;
  c.x = A - (  E + F + G + H ) / 2;
  c.y = C + (  E - F + G - H ) / 2;
  c.z = D + (  E - F - G + H ) / 2;
}

void ang3Rad_To_Deg( ang3_t a )
{
  a.x *= RAD_TO_DEG;
  a.y *= RAD_TO_DEG;
  a.z *= RAD_TO_DEG;
}

void ang3Deg_To_Rad( ang3_t a )
{
  a.x *= DEG_TO_RAD;
  a.y *= DEG_TO_RAD;
  a.z *= DEG_TO_RAD;
}

/** @} (end addtogroup kinetic) */
/** @} (end addtogroup Application) */