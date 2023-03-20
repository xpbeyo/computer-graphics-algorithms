// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs:
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  if (!is_moon) {
    return identity();
  }
  else {
    float angle = 2 * M_PI * (time / 4.0);
    return translate(2 * vec3(cos(angle), 0, sin(angle))) * uniform_scale(0.3) * rotate_about_y(angle);
  }
  /////////////////////////////////////////////////////////////////////////////
}
