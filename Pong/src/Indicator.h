#pragma once

#include "Light.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "mat4.h"


class Indicator {
private:
	vec3 pos, size;
	vec4 color;
	VertexArray* vao;
	IndexBuffer* ibo;
	Light* light;
	mat4 model;

public:
	Indicator(vec3 pos, vec3 size, vec4 color);
	~Indicator();

	void render();

	inline vec3& getPos() { return pos; }
	inline vec4& getColor() { return color; }
};