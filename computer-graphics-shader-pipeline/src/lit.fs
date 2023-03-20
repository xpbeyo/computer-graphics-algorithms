// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  float angle = 2 * M_PI * (animation_seconds / 6.0);
  vec3 light_dir = normalize(vec3(cos(angle), 0.7, sin(angle)));
  vec3 view_dir = -normalize(view_pos_fs_in.xyz);
  
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
    p = 100;
  }
  color = blinn_phong(ka, kd, ks, p, normalize(normal_fs_in), view_dir, light_dir);
}
