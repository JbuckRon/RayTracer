#version 430 core

in vec3 reflection_dir;

out vec4 fcolor;

uniform samplerCube cubeMap;

void main()
{
	fcolor = texture(cubeMap, reflection_dir);
}
