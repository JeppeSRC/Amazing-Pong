#include "Indicator.h"
#include "Shader.h"
#include <glew.h>

Indicator::Indicator(vec3 pos, vec3 size, vec4 color) : pos(pos), color(color), size(size) {

	float vertices[] = {
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		0, 1, 0
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float colors[] = {
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1
	};

	vao = new VertexArray();
	vao->submit(vertices, 12, 3, 0);
	vao->submit(colors, 16, 4, 4);

	ibo = new IndexBuffer(indices, 6);

	light = new Light(pos, color, 3, 1);
	model = mat4::translate(pos) * mat4::scale(size);
}

Indicator::~Indicator() {
	delete ibo;
	delete vao;
}

void Indicator::render() {
	vao->bind();
	ibo->bind();

	Shader::active->setMat4("model", model);
	glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, 0);

	vao->unbind();
	ibo->unbind();

	light->render();
}