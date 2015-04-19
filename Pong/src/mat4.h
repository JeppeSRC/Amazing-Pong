#pragma once

class vec3;

class mat4 {
public:
	mat4(){}
	~mat4(){}

	static mat4 identity();
	static mat4 scale(const vec3& v);
	static mat4 scale(float x, float y, float z);
	static mat4 translate(const vec3& v);
	static mat4 translate(float x, float y, float z);
	static mat4 rotate(const vec3& v);
	static mat4 rotate(float x, float y, float z);
	static mat4 projection(float fov, float width, float height, float zNear, float zFar);
	static mat4 ortho(float left, float right, float top, float bottom, float zNear, float zFar);
		

		
	inline mat4 operator*(mat4& const r) const {
		mat4 res;

		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				res.set(j, i, m[j + 0 * 4] * r.get(0, i) +
								m[j + 1 * 4] * r.get(1, i) + 
								m[j + 2 * 4] * r.get(2, i) + 
								m[j + 3 * 4] * r.get(3, i));
			}
		}

		return res;
	}

	inline void set(int x, int y, float v) { m[x + y * 4] = v; }
	inline float get(int x, int y) { return m[x + y * 4]; }

	inline const float* toArray() const { return m; }

public:
	float m[16];
};
