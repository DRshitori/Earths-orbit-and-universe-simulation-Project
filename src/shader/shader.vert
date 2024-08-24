#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

out vec2 textCoords;
out vec3 fragPosition;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = model * vec4(position, 1.0);
	fragPosition = vec3(projection * view * model * vec4(position, 1.0));
	normal = mat3(transpose(inverse(projection * view * model))) * position;
	textCoords = textureCoords;
}






//#version 330 core
//
//layout(location = 0) in vec3 pos;
//layout(location = 1) in vec3 u_color;
//layout(location = 2) in vec2 tex;
//
//out vec4 fColor;
//out vec2 TextureCoord;
//uniform mat4 MVP;
//
//void main()
//{
//   gl_Position = MVP * vec4(pos,1.0);
//   fColor = vec4(u_color, 1.0f);
//   TextureCoord = tex;
//}
//



//#version 330 core
//
//layout(location = 0) in vec3 pos;
//layout(location = 1) in vec3 VertexNormal;
//
//out vec3 vNormal;
//uniform mat4 MVP;
//out vec4 vPos;
//uniform mat4 Model;
//
//void main()
//{
//   gl_Position = MVP * vec4(pos,1.0);
//   vNormal = VertexNormal;
//	vPos = Model * vec4(pos, 1);
//}
//
//

