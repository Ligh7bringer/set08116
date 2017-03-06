#version 440

// A directional light structure
struct directional_light {
  vec4 ambient_intensity;
  vec4 light_colour;
  vec3 light_dir;
};

// A material structure
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Directional light for the scene
uniform directional_light light;
// Material of the object
uniform material mat;
// Position of the camera
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
  // Calculate ambient component
  vec4 amb_comp = light.ambient_intensity * mat.diffuse;
  // Calculate diffuse component
  vec4 diff_comp = max(dot(normal, light.light_dir),0.0) * mat.diffuse_reflection * light.light_colour;
  // Calculate view direction
  vec3 view_dir = eye_pos - normalize(position);
  // Calculate half vector
  vec4 half_vec = normalize(view_dir + light.light_dir);
  // Calculate specular component
  vec4 spec_comp = pow(max(dot(normal, half_vec),0.0), mat.shininess) * mat.specular_reflection * light.light_colour;
  // Sample texture
  vec4 tex_colour = texture(tex,tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + amb_comp + diff_comp;
  primary.a = 1.0;
  // Calculate final colour - remember alpha
  colour = primary * tex_colour + spec_comp;
  colour.a = 1.0;
  // *********************************
}