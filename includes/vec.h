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

typedef struct s_rgb
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} t_rgb;

typedef struct s_rgba
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} t_rgba;


typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3 a;
	t_vec3 b;
} t_ray;

t_vec3 vec3_mul_float(t_vec3 v, float x);

t_vec3 vec3_add_float(t_vec3 v, float x);

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2);

t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2);

t_vec3 vec3_mul(t_vec3 v1, t_vec3 v2);

t_vec3 vec3_dot(t_vec3 v1, t_vec3 v2);

float dot(t_vec3 v1, t_vec3 v2);

float length(t_vec3 v);

t_vec3 point_at_parameter(float t, t_ray r);