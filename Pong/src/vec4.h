#pragma once

class vec4 {
public:
	vec4(float x = 0, float y = 0, float z = 0, float w = 0);
	~vec4();

public:
	float x, y, z, w;

public:

	inline vec4 operator+(const vec4& v) {
		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	inline vec4& operator+=(const vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	inline vec4 operator-(const vec4& v) {
		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	inline vec4& operator-=(const vec4& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
};