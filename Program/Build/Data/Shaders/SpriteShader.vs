attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;
uniform 	mat4 	u_matWorld;
uniform 	float 	u_alpha;
uniform 	vec2 	u_data;
uniform 	vec2 	u_pos;

varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	
	float disX = (1.0 / u_data.x);
	float disY = (1.0 / u_data.y);
	float xx=a_uv.x/u_data.x + disX * u_pos.x;
	float yy=a_uv.y/u_data.y + disY * u_pos.y;
	v_uv = vec2(xx,yy); 
	
	// v_uv = a_uv;
}
   