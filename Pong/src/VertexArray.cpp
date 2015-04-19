#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(BUFFERS, buffer);
	currBuffer = 0;
}

VertexArray::~VertexArray() {
	glDeleteBuffers(BUFFERS, buffer);
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::submit(float* data, unsigned int size, unsigned short comp, unsigned short index) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[currBuffer++]);
	glBufferData(GL_ARRAY_BUFFER, size * 4, data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, comp, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexArray::bind() const { glBindVertexArray(vao); }
void VertexArray::unbind() const { glBindVertexArray(0); }


