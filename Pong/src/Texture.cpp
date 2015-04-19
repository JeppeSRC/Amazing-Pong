#include "Texture.h"
#include <glew.h>
#include "stb_image.h"

Texture::Texture(const char* filename){

	int w, h, c;

	unsigned char* data = stbi_load(filename, &w, &h, &c, 4);

	if (data){

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

}

Texture::Texture(int width, int height, int col){

	unsigned int* data = new unsigned int[width * height];

	unsigned int a = (col & 0xff000000) >> 24;
	unsigned int r = (col & 0xff0000) >> 16;
	unsigned int g = (col & 0xff00) >> 8;
	unsigned int b = (col & 0xff);

	for (int i = 0; i < (width * height) / 4; i++){
		data[i * 4] = r;
		data[i * 4+1] = g;
		data[i * 4+2] = b;
		data[i * 4+3] = a;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, data);

	delete[] data;
}

void Texture::bind(unsigned int unit){
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture(){
	glDeleteTextures(1, &texture);
}
