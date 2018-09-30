#version 330 core

in vec2 vPos;
in vec4 vColors;
in vec2 vUvs;

out vec4 color;
uniform sampler2D texture;

void main(){
	color = texture2D(texture, vUvs) * (vColors/255.0f);
}
