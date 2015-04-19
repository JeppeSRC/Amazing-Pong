#include "BackGround.h"
#include "Shader.h"
#include <glew.h>

BGObject::BGObject(const vec3 pos, const vec3 size, vec4 color) : Renderable(pos, size) {
	setColor(color);

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


	float texCoords[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};

	float colors[] = {
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w
	};

	vao = new VertexArray();
	vao->submit(vertices, 12, 3, 0);
	vao->submit(texCoords, 8, 2, 1);
	vao->submit(colors, 16, 4, 4);

	ibo = new IndexBuffer(indices, 6);

	model = mat4::translate(pos) * mat4::scale(size);
}


BGObject::~BGObject() {
	if (texture) delete texture;
	delete ibo;
	delete vao;
}

void BGObject::render() {
	vao->bind();
	ibo->bind();

	Shader::active->setMat4("model", model);
	glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, 0);

	vao->unbind();
	ibo->unbind();
}