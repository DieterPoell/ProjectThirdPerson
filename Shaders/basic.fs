#version 330

//Basic Fragment Shader "template". Please do not touch!

uniform sampler2D colorMap;
uniform sampler2D normalMap;

in vec2 texCoord;

in float diffuse;

out vec4 fragment; // to screenbuffer

void main() {

	fragment = diffuse * texture( colorMap, texCoord );
	//fragment = vec4(1.0, 0.0, 0.0, 1.0);

}
