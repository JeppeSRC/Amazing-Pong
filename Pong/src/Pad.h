#pragma once
#include "Renderable.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "mat4.h"
#include "Ball.h"

class Pad : public Renderable {
private:
	Light* top;
	Light* topC;
	Light* center;
	Light* bottomC;
	Light* bottom;
	VertexArray* vao;
	IndexBuffer* ibo;
	mat4 model;

public:
	Pad(vec3 pos, vec3 size, vec4 color);
	~Pad();

	void update() override;
	void render() override;
};
