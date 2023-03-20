// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step

float improved_perlin_noise( vec3 st) 
{
  float dot_products[8];
  int counter = 0;
  for (int i = int(floor(st.x)); i <= int(floor(st.x)) + 1; i++) {
    for (int j = int(floor(st.y)); j <= int(floor(st.y)) + 1; j++) {
      for (int k = int(floor(st.z)); k <= int(floor(st.z)) + 1; k++) {
        vec3 corner = vec3(i, j, k);
        dot_products[counter] = dot(st - corner, random_direction(corner));
        counter ++;
      }
    }
  }

  // Trilinear Interpolation
  vec3 smooth_factor = improved_smooth_step(st - floor(st));
  float c00, c01, c10, c11;
  float c0, c1;

  c00 = dot_products[0] + smooth_factor.x * (dot_products[4] - dot_products[0]);
  c01 = dot_products[1] + smooth_factor.x * (dot_products[5] - dot_products[1]);
  c10 = dot_products[2] + smooth_factor.x * (dot_products[6] - dot_products[2]);
  c11 = dot_products[3] + smooth_factor.x * (dot_products[7] - dot_products[3]);

  c0 = c00 + smooth_factor.y * (c10 - c00);
  c1 = c01 + smooth_factor.y * (c11 - c01);

  return (c0 + smooth_factor.z * (c1 - c0));
}

