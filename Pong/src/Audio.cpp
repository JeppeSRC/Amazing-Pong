#include "Audio.h"
#include <WaveManager.h>
#include <al.h>
#include <alext.h>
#include <stdio.h>

Audio::Audio(const char* filename) {
	pos = new vec3(500, 300);
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	WaveFile file = LoadWaveFile(filename);

	alBufferData(buffer, file.FORMAT, file.data, file.getSize(), file.getSmapleRate());

	alSourcei(source, AL_BUFFER, buffer);
}

Audio::~Audio() {
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
}

void Audio::play() {
	alSource3f(source, AL_POSITION, pos->x / 500.0f - 1.0f, pos->y / 300.0f - 1.0f, 0);
	alSourcePlay(source);
}

void Audio::pause() {
	alSourcePause(source);
}

void Audio::stop() {
	alSourceStop(source);
}

void Audio::loop() {
	
}

void Audio::setPos(vec3* pos) {
	this->pos = pos;
}