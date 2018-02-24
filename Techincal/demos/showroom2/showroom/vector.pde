class vec3_t
{
  float    i;             /**< \$f\hat{i}\$f value */
  float    j;             /**< \$f\hat{j}\$f value */
  float    k;             /**< \$f\hat{k}\$f value */
};

float len3( vec3_t v )
{
  float i_2 = v.i * v.i;
  float j_2 = v.j * v.j;
  float k_2 = v.k * v.k;
  return sqrt( i_2 + j_2 + k_2 );
}

float ZDIV( float a, float b)
{
  if( b != 0 ) return a/b;
  else return 1000;
}

void nrm3( vec3_t v )
{
  float length = len3( v );
  if (length == 0 || length == 1) return;
  v.i /= length;
  v.j /= length;
  v.k /= length;
}

void sub3( vec3_t x, vec3_t y )
{
  x.i = x.i - y.i;
  x.j = x.j - y.j;
  x.k = x.k - y.k;
}

/* Dot product of two vectors */
float dot3( vec3_t u, vec3_t v )
{
  return u.i * v.i + u.j * v.j + u.k * v.k;
}

/* Angle between two vectors */
float ang3( vec3_t u, vec3_t v)
{
  return acos( ZDIV( dot3( u, v ), ( len3(u) * len3(v) ) ) );
}

/* Multiply a vector by a scalar */
void mul3( float m, vec3_t v, vec3_t r )
{
  r.i = m * v.i;
  r.j = m * v.j;
  r.k = m * v.k;
}

/* Cross product of two vectors */
void cross3( vec3_t u, vec3_t v, vec3_t r )
{
  r.i = u.j*v.k - u.k*v.j;
  r.j = u.k*v.i - u.i*v.k;
  r.k = u.i*v.j - u.j*v.i;
}

/* Add three vectors */
void add33( vec3_t u, vec3_t v, vec3_t w, vec3_t r)
{
  r.i = u.i + v.i + w.i;
  r.j = u.j + v.j + w.j;
  r.k = u.k + v.k + w.k;
}

/** @} (end addtogroup kinetic) */
/** @} (end addtogroup Application) */