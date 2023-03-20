// Inputs:
//   t  3D vector by which to translate
// Return a 4x4 matrix that translates and 3D point by the given 3D vector
mat4 translate(vec3 t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  mat4 i = identity();
  i[3][0] = t[0];
  i[3][1] = t[1];
  i[3][2] = t[2];
  i[3][3] = 1;
  return i;
  /////////////////////////////////////////////////////////////////////////////
}

