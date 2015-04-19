#pragma once
#include "Renderable.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "mat4.h"

class BGObject : public Renderable {
private:
	VertexArray* vao;
	IndexBuffer* ibo;
	mat4 model;

public:
	BGObject(const vec3 pos, const vec3 size, vec4 color);
	~BGObject();

	void render() override;

};