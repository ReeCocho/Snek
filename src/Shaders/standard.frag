#version 330 core

out vec4 outColor;

in vec2 UV;

uniform sampler2D sprite;
uniform vec4 color;

void main()
{
	outColor = texture(sprite, UV) * color;
}