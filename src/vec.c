#include "../includes/minirt.h"

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

t_vec3 vec3_dot(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
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