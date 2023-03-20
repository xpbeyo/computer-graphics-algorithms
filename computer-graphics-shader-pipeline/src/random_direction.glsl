// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec2 rand2 = random2(seed);
  float phi = rand2.x * M_PI;
  float theta = rand2.y * 2 * M_PI;
  return normalize(vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi)));
  /////////////////////////////////////////////////////////////////////////////
}
