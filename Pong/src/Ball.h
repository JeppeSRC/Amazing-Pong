#pragma once
#include "Renderable.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Light.h"
#include "vec4.h"
#include "mat4.h"

class Ball : public Renderable {
private:
	vec3 vel;
	VertexArray* vao;
	IndexBuffer* ibo;
	mat4 model;
	Light* light;

	void initLight();
	
public:
	Ball(vec3 pos, vec3 size, vec4 color);
	Ball(vec3 pos, vec3 size, vec4 color, Texture* texture);
	~Ball();

	void update() override;
	void render() override;

	inline vec3& getVel() { return vel; }
};