#pragma once


class IndexBuffer {
private:
	unsigned int ibo;
	unsigned int count;
public:
	IndexBuffer(unsigned int* indices, unsigned int size);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline const unsigned int getCount() const { return count; }
};