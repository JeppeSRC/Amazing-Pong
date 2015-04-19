#pragma once

#define BUFFERS 5

class VertexArray {
private:
	unsigned int vao;
	unsigned int buffer[BUFFERS];
	unsigned short currBuffer;

public:
	VertexArray();
	~VertexArray();

	void submit(float* data, unsigned int size, unsigned short comp, unsigned short index);

	void bind() const;
	void unbind() const;
};