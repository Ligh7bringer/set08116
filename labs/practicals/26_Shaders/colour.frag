#version 440

// *********************************
// Define the output colour for the shader here
uniform vec4 colour;
uniform vec4 colour2;
// *********************************

// Outgoing colour for the shader
layout(location = 0) out vec4 out_colour;
layout(location = 0) out vec4 out_colour2;

void main() {
  // *********************************
  // Set outgoing colour
  out_colour=colour + colour2;
  //out_colour2 = colour2;
  // *********************************
}