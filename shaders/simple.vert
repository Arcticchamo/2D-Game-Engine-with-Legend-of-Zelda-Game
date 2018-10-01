attribute vec3 in_Position;
attribute vec4 in_Color;

varying vec4 ex_Color;

uniform mat4 in_ModelMat;
uniform mat4 in_ViewMat;
uniform mat4 in_ProjectionMat;

void main()
{
 gl_Position = in_ProjectionMat * in_ViewMat * in_ModelMat * vec4 (in_Position, 1);
 ex_Color = in_Color;
}
