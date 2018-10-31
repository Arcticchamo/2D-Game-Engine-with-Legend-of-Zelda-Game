uniform mat4 in_ModelMat;
uniform mat4 in_ViewMat;
uniform mat4 in_ProjectionMat;

attribute vec3 in_Position;
attribute vec2 in_TexCoord;

varying vec2 ex_TexCoord;

void main()
{
	gl_Position = in_ProjectionMat * in_ViewMat * in_ModelMat * vec4(in_Position, 1);
	ex_TexCoord = in_TexCoord;
}
