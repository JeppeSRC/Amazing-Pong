#include "Audio.h"
#include <al.h>
#include <alext.h>
#include <stdio.h>

struct RIFFHeader {
	char ChunkID[4];
	unsigned int ChunkSize;
	unsigned int Format;
};

struct FormatHeader {
	char SubChunk1ID[4];
	unsigned int SubChunk1Size;
	unsigned short Format;
	unsigned short Channels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	unsigned short BlockAlign;
	unsigned short BitsPerSample;
};

struct DataHeader {
	char SubChunk2ID[4];
	unsigned int SubChunk2Size;
};

struct WaveHeader {
	RIFFHeader riff;
	FormatHeader format;
	DataHeader data;
	unsigned char* rawData = nullptr;

	~WaveHeader() { delete[] rawData; }
};

unsigned int getOpenALFormat(WaveHeader* wave) {
	switch (wave->format.Channels) {
		case 1:
		switch (wave->format.BitsPerSample) {
			case 8:
				return AL_FORMAT_MONO8;
			case 16:
				return AL_FORMAT_MONO16;
			case 32:
				return AL_FORMAT_MONO_FLOAT32;
		}

		case 2:
			switch (wave->format.BitsPerSample) {
				case 8:
					return AL_FORMAT_STEREO8;
				case 16:
					return AL_FORMAT_STEREO16;
				case 32:
					return AL_FORMAT_STEREO_FLOAT32;
			}

		case 6:
			switch (wave->format.BitsPerSample) {
				case 8:
					return AL_FORMAT_51CHN8;
				case 16:
					return AL_FORMAT_51CHN16;
				case 32:
					return AL_FORMAT_51CHN32;
			}

		case 8:
			switch (wave->format.BitsPerSample) {
				case 8:
					return AL_FORMAT_71CHN8;
				case 16:
					return AL_FORMAT_71CHN16;
				case 32:
					return AL_FORMAT_71CHN32;
			}
	}

	return 0;
}

void loadWaveFile(const char* filename, WaveHeader* wave) {

	FILE* file = fopen(filename, "rb");

	if (!file) {
		printf("Failed to open file: %s\n", filename);
		return;
	}


	fread(wave, sizeof(WaveHeader) - sizeof(unsigned char*), 1, file);

	if (wave->riff.ChunkID[0] != 'R' || wave->riff.ChunkID[1] != 'I' || wave->riff.ChunkID[2] != 'F' || wave->riff.ChunkID[3] != 'F') { printf("Inavlid RIFF chunk!\n");return; }

	if (wave->format.SubChunk1ID[0] != 'f' || wave->format.SubChunk1ID[1] != 'm' || wave->format.SubChunk1ID[2] != 't' || wave->format.SubChunk1ID[3] != ' ') { printf("Inavlid FORMAT chunk!\n");return; }

	if (wave->data.SubChunk2ID[0] != 'd' || wave->data.SubChunk2ID[1] != 'a' || wave->data.SubChunk2ID[2] != 't' || wave->data.SubChunk2ID[3] != 'a') { printf("Inavlid DATA chunk!\n");return; }

	wave->rawData = new unsigned char[wave->data.SubChunk2Size];

	fread(wave->rawData, wave->data.SubChunk2Size, 1, file);
}

Audio::Audio(const char* filename) {
	pos = new vec3(500, 300);
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	WaveHeader header;

	loadWaveFile(filename, &header);

	alBufferData(buffer, getOpenALFormat(&header), header.rawData, header.data.SubChunk2Size, header.format.SampleRate);

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