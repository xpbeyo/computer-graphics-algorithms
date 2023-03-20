// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  T = normalize((rotate_about_y(M_PI / 2.0) * vec4(N, 0)).xyz);
  B = normalize(cross(N, T));
}
