#include "../includes/minirt.h"

t_vec2 vec2_mul_float(t_vec2 v, float x)
{
	t_vec2 res;

	res.x = v.x * x;
	res.y = v.y * x;
	return (res);
}

t_vec3 vec3_mul_float(t_vec3 v, float x)
{
	t_vec3 res;

	res.x = v.x * x;
	res.y = v.y * x;
	res.z = v.z * x;
	return (res);
}

t_vec3 vec3_add_float(t_vec3 v, float x)
{
	t_vec3 res;

	res.x = v.x + x;
	res.y = v.y + x;
	res.z = v.z + x;
	return (res);
}

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec3 vec3_mul(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec3 vec3_dot_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

float vec3_dot_float(t_vec3 v1, t_vec3 v2)
{
	float res;

	res = 0.0f;
	res += v1.x * v2.x;
	res += v1.y * v2.y;
	res += v1.z * v2.z;
	return (res);
}

float dot(t_vec3 v1, t_vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float length(t_vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3 point_at_parameter(float t, t_ray r)
{
	t_vec3 res;

	res = vec3_add(r.a, vec3_mul_float(r.b, t));
	return (res);
}

t_vec3 vec3_normalize(t_vec3 v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	// Check if the length is not zero to avoid division by zero
	if (length != 0.0f) {
	    v.x /= length;
	    v.y /= length;
	    v.z /= length;
	}
	return v;
}

t_vec4 vec4_normalize(t_vec4 v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);

	// Check if the length is not zero to avoid division by zero
	if (length != 0.0f) {
	    v.x /= length;
	    v.y /= length;
	    v.z /= length;
	    v.w /= length;
	}
	return v;
}

t_vec4 vec3_to_vec4(t_vec3 v, float f)
{
	t_vec4 res;

	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	res.w = f;
	return (res);
}

t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}




t_vec3 vec3_angle_axis(float angle, t_vec3 axis)
{
	t_vec3 result;

	float halfAngle = angle * 0.5f;
	float sinHalfAngle = sin(halfAngle);
	result.x = axis.x * sinHalfAngle;
	result.y = axis.y * sinHalfAngle;
	result.z = axis.z * sinHalfAngle;
	return result;
}

// Function to rotate a 3D vector using a quaternion
t_vec3 vec3_rotate(t_vec3 v, t_vec3 q)
{
	t_vec3 t = { 2.0f * (q.y * v.z - q.z * v.y),
	             2.0f * (q.z * v.x - q.x * v.z),
	             2.0f * (q.x * v.y - q.y * v.x) };
	t_vec3 result;
	result.x = v.x + q.y * t.z - q.z * t.y;
	result.y = v.y + q.z * t.x - q.x * t.z;
	result.z = v.z + q.x * t.y - q.y * t.x;
	return result;
}


t_mat4	mat4_mul_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4 m;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m.m[i][j] = a.m[i][0] * b.m[0][j] +
						a.m[i][1] * b.m[1][j] +
						a.m[i][2] * b.m[2][j] +
						a.m[i][3] * b.m[3][j];
		}
	}
	return (m);
}