#include "AudioManager.h"
#include <stdio.h>

ALCdevice* AudioManager::device;
ALCcontext* AudioManager::cxt;
Audio* AudioManager::ballHit;
Audio* AudioManager::ballHit_2;

void AudioManager::Init() {
	AudioManager::device = alcOpenDevice(NULL);
	AudioManager::cxt = alcCreateContext(device, 0);
	alcMakeContextCurrent(AudioManager::cxt);

	printf("OpenAL Version: %s\n", alGetString(AL_VERSION));
	printf("Vendor: %s\n", alGetString(AL_VENDOR));
	printf("Renderer: %s\n", alGetString(AL_RENDERER));
	Load();
}

void AudioManager::Destroy() {
	Destruct();
	alcDestroyContext(AudioManager::cxt);
	alcCloseDevice(AudioManager::device);
}

void AudioManager::Load() {
	ballHit = new Audio("./res/ballHit.wav");
	ballHit_2 = new Audio("./res/ballHit_2.wav");
}

void AudioManager::Destruct() {
	delete ballHit, ballHit_2;
}