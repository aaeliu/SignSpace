#version 330 core

out vec4 FragColor;
in vec2 pos;
void main () {
  FragColor = vec4(pos, 0.f, 1.0f);
}