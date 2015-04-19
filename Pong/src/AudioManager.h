#pragma once
#include <al.h>
#include <alc.h>
#include <alext.h>
#include "Audio.h"


class AudioManager {
private:
	static ALCdevice* device;
	static ALCcontext* cxt;
	static void Load();
	static void Destruct();
public:
	static void Init();
	static void Destroy();

	static Audio* ballHit;
	static Audio* ballHit_2;
};