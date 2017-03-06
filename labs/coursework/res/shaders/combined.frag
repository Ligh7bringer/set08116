#version 440

// Incoming vertex colour
layout(location = 0) in vec4 vertex_colour;

layout(location = 2) in vec2 tex_coords;

// Outgoing colour
layout(location = 0) out vec4 colour;

//layout (location = 2) out vec2 tex_coords_out;

void main() {
  // *********************************
  // Set outgoing vertex colour
  colour=vertex_colour;
  // *********************************
}
