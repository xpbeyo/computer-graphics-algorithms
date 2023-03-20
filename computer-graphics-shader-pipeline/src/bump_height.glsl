// // Create a bumpy surface by using procedural noise to generate a height (
// // displacement in normal direction).
// //
// // Inputs:
// //   is_moon  whether we're looking at the moon or centre planet
// //   s  3D position of seed for noise generation
// // Returns elevation adjust along normal (values between -0.1 and 0.1 are
// //   reasonable.
// float bump_height( bool is_moon, vec3 s)
// {
//   if (is_moon) {
//     return 0.1 * smooth_heaviside(improved_perlin_noise(s), 1000);
//   }
//   else {
//     return 0.05 * smooth_heaviside(improved_perlin_noise(s), 10);
//   }
// }

// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.

float bump_height( bool is_moon, vec3 s)
{
  if (!is_moon) {
    return 0.1 * smooth_heaviside(improved_perlin_noise(vec3(s.x, s.y, s.x + s.y + s.z)), 2);
  }
  else {
    return 0.1 * smooth_heaviside(improved_perlin_noise(vec3(s.x, s.y, s.x + s.y + s.z)), 0.5);
  }
}
