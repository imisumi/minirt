#ifndef T_H
# define T_H

#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec3 vec3_create(float x, float y, float z) {
    vec3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

vec3 vec3_add(vec3 v1, vec3 v2) {
    vec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

vec3 vec3_scale(vec3 v, float s) {
    vec3 result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    return result;
}

float vec3_length(vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 vec3_unit_vector(vec3 v) {
    float length = vec3_length(v);
    return vec3_scale(v, 1.0f / length);
}

vec3 vec3_cross(vec3 v1, vec3 v2) {
    vec3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = -(v1.x * v2.z - v1.z * v2.x);
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

float vec3_dot(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void vec3_make_unit_vector(vec3* v) {
    float k = 1.0f / vec3_length(*v);
    v->x *= k;
    v->y *= k;
    v->z *= k;
}

#endif