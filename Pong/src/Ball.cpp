#include "Ball.h"
#include <glew.h>
#include "Shader.h"

Ball::Ball(vec3 pos, vec3 size, vec4 color, Texture* texture) : Renderable(pos, size) {
	setTexture(texture);
	setColor(vec4(1, 1, 1, 1));
	vel = vec3(7.5,5.5);
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

	initLight();
}


Ball::Ball(vec3 pos, vec3 size, vec4 color) : Renderable(pos, size) {
	setTexture(nullptr);
	setColor(color);
	vel = vec3(1);
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

	initLight();
}
 
Ball::~Ball() {
	delete light;
}

void Ball::initLight() {
	light = new Light(pos + (size / 2.0f), color, 4, 0.5);
}

void Ball::update(float delta) {



	pos += vel * delta;
	model = mat4::translate(pos) * mat4::scale(size);

	light->getPos() = pos + (size / 2);

	light->render();

}

void Ball::render() {
	vao->bind();
	ibo->bind();

	if (texture != nullptr) {
		texture->bind();
		Shader::active->setInt("tex", 1);
	}

	Shader::active->setMat4("model", model);
	glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, 0);

	Shader::active->setInt("tex", 0);

	vao->unbind();
	ibo->unbind();
}