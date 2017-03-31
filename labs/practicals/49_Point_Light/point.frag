#version 440

// Point light information
struct point_light {
  //float range;
  vec4 light_colour;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

// Material information
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Point light for the scene
uniform point_light point;
// Material for the object
uniform material mat;
// Eye position
uniform vec3 eye_pos;
// Texture
uniform sampler2D tex;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {
  // *********************************
  // Get distance between point light and vertex
  float dist = distance(point.position, position);
  // Calculate attenuation factor
  float att_factor = 1/(point.constant + (point.linear * dist) + (point.quadratic*(dist*dist))) * point.light_colour;
  // Calculate light colour

  // Calculate light dir
  vec3 light_dir = point.position * position;
  // Now use standard phong shading but using calculated light colour and direction
  // - note no ambient
  // Calculate diffuse component
  vec4 diffuse = max(dot(normal, light_dir),0.0) * mat.diffuse_reflection * light_colour;
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Calculate half vector
  vec3 half_vec = normalize(view_dir + light_dir);
  // Calculate specular component
  vec4 specular = pow(max(dot(normal, half_vec),0.0), mat.shininess) * mat.specular_reflection * light_colour;
  // Sample texture
  vec4 tex_colour = texture(tex,tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  primary.a = 1.0;
  // Calculate final colour - remember alpha
  colour = primary * tex_colour + specular;
  colour.a = 1.0;
  // *********************************
}
