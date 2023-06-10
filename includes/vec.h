#include "minirt.h"


// typedef struct s_ray
// {
// 	t_vec3 a;
// 	t_vec3 b;
// } t_ray;

// typedef struct s_vec3
// {
// 	float x;
// 	float y;
// 	float z;
// } t_vec3;

// typedef struct s_rgb
// {
// 	uint8_t r;
// 	uint8_t g;
// 	uint8_t b;
// } t_rgb;

// typedef struct s_rgba
// {
// 	uint8_t r;
// 	uint8_t g;
// 	uint8_t b;
// 	uint8_t a;
// } t_rgba;


// typedef struct s_vec2
// {
// 	float	x;
// 	float	y;
// }	t_vec2;

// typedef struct s_vec3
// {
// 	float	x;
// 	float	y;
// 	float	z;
// }	t_vec3;

// typedef struct s_vec4
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	w;
// }	t_vec4;

// typedef struct s_ray
// {
// 	t_vec3 a;
// 	t_vec3 b;
// } t_ray;

t_vec2 vec2_mul_float(t_vec2 v, float x);
t_vec3 vec3_mul_float(t_vec3 v, float x);

t_vec3 vec3_add_float(t_vec3 v, float x);

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2);

t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2);

t_vec3 vec3_mul(t_vec3 v1, t_vec3 v2);

t_vec3 vec3_dot_vec3(t_vec3 v1, t_vec3 v2);
float vec3_dot_float(t_vec3 v1, t_vec3 v2);

float dot(t_vec3 v1, t_vec3 v2);

float length(t_vec3 v);

t_vec3 point_at_parameter(float t, t_ray r);

t_vec3 vec3_normalize(t_vec3 v);
t_vec4 vec4_normalize(t_vec4 v);

t_vec4 vec3_to_vec4(t_vec3 v, float f);

t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2);


t_vec3 vec3_angle_axis(float angle, t_vec3 axis);
t_vec3 vec3_rotate(t_vec3 v, t_vec3 q);



// t_mat4 mat4_lookAt(t_vec3 eye, t_vec3 center, t_vec3 up);
t_mat4 mat4_lookAt(t_vec3 pos, t_vec3 target, t_vec3 up);
t_mat4 mat4_identity();
t_mat4 mat4_translate(t_vec3 translation);


float determinant(const t_mat4 matrix);

t_mat4 inverse_mat4(t_mat4 matrix);

void print_matrix(t_mat4 matrix);


t_mat4	mat4_mul_mat4(t_mat4 a, t_mat4 b);