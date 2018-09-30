#version 330 core
layout(location=0) in vec2 vertexPositions;
layout(location=1) in vec2 vertexUvs;
layout(location=2) in vec4 vertexColors;

out vec2 vPos;
out vec4 vColors;
out vec2 vUvs;

uniform mat4 orthographicMatrix;

void main(){
	gl_Position = orthographicMatrix * vec4(vertexPositions.x, vertexPositions.y, 1.0, 1.0);
	vPos = vertexPositions;
	vColors = vertexColors;
	vUvs = vertexUvs;
}
