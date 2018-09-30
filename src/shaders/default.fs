#version 330 core
//in vec2 vPos;
in vec4 vColors;
//in vec2 vUvs;

out vec4 color;

void main(){
	color = vColors/255.0f; // conversion from 255
}
