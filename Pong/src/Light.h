#pragma once
#include "vec3.h"
#include "vec4.h"

#define MAX_LIGHTS 20

class Light {
private:
	vec3 pos;
	vec4 color;
	float range, damper;
	char strPos[64];
	char strCol[64];
	char strRange[64];
	char strDamp[64];
	static unsigned short lights;
	unsigned int index;

public:
	Light(vec3 pos, vec4 color, float range = 15.0f, float damper = 0.925f);
	~Light();

	void render();

	inline vec3& getPos() { return pos; }
	inline vec4& getColor() { return color; }
	inline float& getRange() { return range; }
	inline float& getDamper() { return damper; }
	inline void setPos(const vec3& pos) { this->pos = pos; }
	inline void setColr(const vec4& color) { this->color = color; }
	inline void setRange(float range) { this->range = range; }
	inline void setDamper(float damper) { this->damper = damper; }

	inline static const unsigned int getTotalLights() { return Light::lights; }
};