#pragma once

class vec3 {
public:
	vec3(float x = 0, float y = 0, float z = 0);
	~vec3();

public:
	float x, y, z;

public:

	inline vec3 operator+(const vec3& v) {
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	inline vec3& operator+=(const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline vec3 operator-(const vec3& v) {
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	inline vec3& operator-=(const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	inline vec3 operator/(const vec3& v) {
		return vec3(x / v.x, y / v.y, z / v.z);
	}

	inline vec3 operator/(const float v) {
		return vec3(x / v, y / v, z / v);
	}

	inline vec3 operator*(const vec3& v) {
		return vec3(x * v.x, y * v.y, z * v.z);
	}

	inline vec3 operator*(float v) {
		return vec3(x * v, y * v, z * v);
	}
};