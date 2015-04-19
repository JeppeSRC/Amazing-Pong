#pragma once
#include "vec3.h"

class Audio {
private:
	unsigned int buffer, source;
	vec3* pos;

public:
	Audio(const char* filename);
	~Audio();

	void play();
	void pause();
	void stop();
	void loop();
	void setPos(vec3* pos);
};