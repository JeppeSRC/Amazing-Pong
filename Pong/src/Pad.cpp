#include "Pad.h"
#include "Shader.h"
#include "vec3.h"
#include <glew.h>

Pad::Pad(vec3 pos, vec3 size, vec4 color) : Renderable(pos, size) {
	setColor(color);
	setTexture(nullptr);

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

	top = new Light(vec3(pos.x + (size.x / 2), pos.y + 5), vec4(1, 1, 1, 1), 4);
	topC = new Light(vec3(pos.x + (size.x / 2), pos.y + (size.y / 4)), vec4(1, 0, 1, 1), 4);
	center = new Light(vec3(pos.x + (size.x / 2), pos.y + (size.y / 2)), vec4(0, 0, 1, 1), 4);
	bottomC = new Light(vec3(pos.x + (size.x / 2), pos.y + size.y - (size.y / 4)), vec4(1, 0, 1, 1), 4);
	bottom = new Light(vec3(pos.x + (size.x / 2), pos.y + size.y - 5), vec4(1, 1, 1, 1), 4);

}

Pad::~Pad() {
	delete vao;
	delete ibo;
	delete top;
	delete topC;
	delete center;
	delete bottomC;
	delete bottom;
}

void Pad::update() {

	//left

	model = mat4::translate(pos) * mat4::scale(size);

	top->getPos().x = pos.x + (size.x / 2);
	top->getPos().y = pos.y + 5;

	topC->getPos().x = pos.x + (size.x / 2);
	topC->getPos().y = pos.y + (size.y / 4);

	center->getPos().x = pos.x + (size.x / 2);
	center->getPos().y = pos.y + (size.y / 2);

	bottomC->getPos().x = pos.x + (size.x / 2);
	bottomC->getPos().y = pos.y + size.y - (size.y / 4);

	bottom->getPos().x = pos.x + (size.x / 2);
	bottom->getPos().y = pos.y + size.y - 5;

	top->render();
	topC->render();
	center->render();
	bottomC->render();
	bottom->render();
}

void Pad::render() {
	vao->bind();
	ibo->bind();

	Shader::active->setMat4("model", model);
	glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, 0);

	ibo->unbind();
	vao->unbind();

	
};