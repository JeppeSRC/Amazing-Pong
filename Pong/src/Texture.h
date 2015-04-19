#pragma once



class Texture {
public:
	Texture(const char* filename);
	Texture(int width, int height, int col);
	~Texture();

	void bind(unsigned int unit = 0);

private:
	unsigned int texture;
};
