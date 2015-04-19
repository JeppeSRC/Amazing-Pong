#include "mat4.h"
#include "vec3.h"
#define _USE_MATH_DEFINES
#include <math.h>

mat4 mat4::identity(){
	mat4 r;

	r.m[0 + 0 * 4] = 1; r.m[0 + 1 * 4] = 0; r.m[0 + 2 * 4] = 0; r.m[0 + 3 * 4] = 0;
	r.m[1 + 0 * 4] = 0; r.m[1 + 1 * 4] = 1; r.m[1 + 2 * 4] = 0; r.m[1 + 3 * 4] = 0;
	r.m[2 + 0 * 4] = 0; r.m[2 + 1 * 4] = 0; r.m[2 + 2 * 4] = 1; r.m[2 + 3 * 4] = 0;
	r.m[3 + 0 * 4] = 0; r.m[3 + 1 * 4] = 0; r.m[3 + 2 * 4] = 0; r.m[3 + 3 * 4] = 1;

	return r;
}

mat4 mat4::scale(const vec3& v){
	return scale(v.x, v.y, v.z);
}

mat4 mat4::scale(float x, float y, float z){
	mat4 r;

	r.m[0 + 0 * 4] = x; r.m[0 + 1 * 4] = 0; r.m[0 + 2 * 4] = 0; r.m[0 + 3 * 4] = 0;
	r.m[1 + 0 * 4] = 0; r.m[1 + 1 * 4] = y; r.m[1 + 2 * 4] = 0; r.m[1 + 3 * 4] = 0;
	r.m[2 + 0 * 4] = 0; r.m[2 + 1 * 4] = 0; r.m[2 + 2 * 4] = z; r.m[2 + 3 * 4] = 0;
	r.m[3 + 0 * 4] = 0; r.m[3 + 1 * 4] = 0; r.m[3 + 2 * 4] = 0; r.m[3 + 3 * 4] = 1;

	return r;
}

mat4 mat4::translate(const vec3& v){
	return translate(v.x, v.y, v.z);
}

mat4 mat4::translate(float x, float y, float z){
	mat4 r;

	r.m[0 + 0 * 4] = 1; r.m[0 + 1 * 4] = 0; r.m[0 + 2 * 4] = 0; r.m[0 + 3 * 4] = x;
	r.m[1 + 0 * 4] = 0; r.m[1 + 1 * 4] = 1; r.m[1 + 2 * 4] = 0; r.m[1 + 3 * 4] = y;
	r.m[2 + 0 * 4] = 0; r.m[2 + 1 * 4] = 0; r.m[2 + 2 * 4] = 1; r.m[2 + 3 * 4] = z;
	r.m[3 + 0 * 4] = 0; r.m[3 + 1 * 4] = 0; r.m[3 + 2 * 4] = 0; r.m[3 + 3 * 4] = 1;

	return r;
}

mat4 mat4::rotate(const vec3& v){
	return rotate(v.x, v.y, v.z);
}

mat4 mat4::rotate(float x, float y, float z){
	mat4 rx, ry, rz;

	x *= M_PI / 180;
	y *= M_PI / 180;
	z *= M_PI / 180;

	float cosx = cosf(x);
	float sinx = sinf(x);
	float cosy = cosf(y);
	float siny = sinf(y);
	float cosz = cosf(z);
	float sinz = sinf(z);

	rx.m[0 + 0 * 4] = 1;	 rx.m[0 + 1 * 4] = 0;		 rx.m[0 + 2 * 4] = 0;		 rx.m[0 + 3 * 4] = 0;
	rx.m[1 + 0 * 4] = 0;	 rx.m[1 + 1 * 4] = cosx;	 rx.m[1 + 2 * 4] = -sinx;	 rx.m[1 + 3 * 4] = 0;
	rx.m[2 + 0 * 4] = 0;	 rx.m[2 + 1 * 4] = sinx;	 rx.m[2 + 2 * 4] = cosx;	 rx.m[2 + 3 * 4] = 0;
	rx.m[3 + 0 * 4] = 0;	 rx.m[3 + 1 * 4] = 0;		 rx.m[3 + 2 * 4] = 0;		 rx.m[3 + 3 * 4] = 1;

	ry.m[0 + 0 * 4] = cosy;	 ry.m[0 + 1 * 4] = 0;		 ry.m[0 + 2 * 4] = -siny;	 ry.m[0 + 3 * 4] = 0;
	ry.m[1 + 0 * 4] = 0;	 ry.m[1 + 1 * 4] = 1;		 ry.m[1 + 2 * 4] = 0;		 ry.m[1 + 3 * 4] = 0;
	ry.m[2 + 0 * 4] = siny;	 ry.m[2 + 1 * 4] = 0;		 ry.m[2 + 2 * 4] = cosy;	 ry.m[2 + 3 * 4] = 0;
	ry.m[3 + 0 * 4] = 0;	 ry.m[3 + 1 * 4] = 0;		 ry.m[3 + 2 * 4] = 0;		 ry.m[3 + 3 * 4] = 1;

	rz.m[0 + 0 * 4] = cosz;	 rz.m[0 + 1 * 4] = -sinz;	 rz.m[0 + 2 * 4] = 0;		 rz.m[0 + 3 * 4] = 0;
	rz.m[1 + 0 * 4] = sinz;	 rz.m[1 + 1 * 4] = cosz;	 rz.m[1 + 2 * 4] = 0;		 rz.m[1 + 3 * 4] = 0;
	rz.m[2 + 0 * 4] = 0;	 rz.m[2 + 1 * 4] = 0;		 rz.m[2 + 2 * 4] = 1;		 rz.m[2 + 3 * 4] = 0;
	rz.m[3 + 0 * 4] = 0;	 rz.m[3 + 1 * 4] = 0;		 rz.m[3 + 2 * 4] = 0;		 rz.m[3 + 3 * 4] = 1;

	return rx * ry * rz;
}

mat4 mat4::projection(float fov, float width, float height, float zNear, float zFar) {
	mat4 r;

	float aspect = (float)width / (float)height;
	float tanHalf = tan(fov / 2);
																																		   
	r.m[0 + 0 * 4] = 1.0f / (aspect * tanHalf);	 r.m[0 + 1 * 4] = 0;			   r.m[0 + 2 * 4] = 0;								   r.m[0 + 3 * 4] = 0;
	r.m[1 + 0 * 4] = 0;							 r.m[1 + 1 * 4] = 1.0f / tanHalf;  r.m[1 + 2 * 4] = 0;								   r.m[1 + 3 * 4] = 0;
	r.m[2 + 0 * 4] = 0;							 r.m[2 + 1 * 4] = 0;			   r.m[2 + 2 * 4] = (-zNear - zFar) / (zNear - zFar);  r.m[2 + 3 * 4] = 2 * zNear * zFar / (zNear - zFar);
	r.m[3 + 0 * 4] = 0;							 r.m[3 + 1 * 4] = 0;			   r.m[3 + 2 * 4] = 1;								   r.m[3 + 3 * 4] = 1;

	return r;
}

mat4 mat4::ortho(float left, float right, float top, float bottom, float zNear, float zFar) {
	mat4 r;


	r.m[0 + 0 * 4] = 2.0f / (right - left); r.m[0 + 1 * 4] = 0;				       r.m[0 + 2 * 4] = 0;					  r.m[0 + 3 * 4] = -(right + left) / (right - left);
	r.m[1 + 0 * 4] = 0;					  r.m[1 + 1 * 4] = 2.0f / (bottom - top); r.m[1 + 2 * 4] = 0;					  r.m[1 + 3 * 4] = -(bottom + top) / (bottom - top);
	r.m[2 + 0 * 4] = 0;				      r.m[2 + 1 * 4] = 0;					   r.m[2 + 2 * 4] = -2.0f / (zFar - zNear); r.m[2 + 3 * 4] = (zFar + zNear) / (zFar - zNear);
	r.m[3 + 0 * 4] = 0;				      r.m[3 + 1 * 4] = 0;					   r.m[3 + 2 * 4] = 0;					  r.m[3 + 3 * 4] = 1;

	return r;
}