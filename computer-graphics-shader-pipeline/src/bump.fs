// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  mat4 model_trans = model(is_moon, animation_seconds);
  float angle = 2 * M_PI * (animation_seconds / 6.0);
  vec3 light_dir = normalize(vec3(cos(angle), 0.7, sin(angle)));
  
  vec3 T;
  vec3 B;
  tangent(sphere_fs_in, T, B);
  vec3 bump_pos = bump_position(is_moon, sphere_fs_in);

  vec3 new_n = normalize(
    cross(
      (bump_position(is_moon, sphere_fs_in + T * 0.0001) - bump_pos) / 0.0001,
      (bump_position(is_moon, sphere_fs_in + B * 0.0001) - bump_pos) / 0.0001
    )
  );
  new_n = normalize((transpose(inverse(view * model_trans)) * vec4(new_n, 1)).xyz);

  vec3 view_dir = -normalize((view * model_trans * vec4(bump_pos, 1)).xyz);

  // Set up the constants
  vec3 ka, kd, ks;
  float p;
  if (!is_moon) {
    ka = vec3(0.01);
    kd = vec3(0, 0, 1);
    ks = vec3(1);
    p = 1000;

  }
  else {
    ka = vec3(0.01);
    kd = vec3(128/255.0, 128/255.0, 128/255.0);
    ks = vec3(0.5);
    p = 1000;
  }
  color = blinn_phong(ka, kd, ks, p, new_n, view_dir, light_dir);
}
