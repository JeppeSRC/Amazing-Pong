#include "Light.h"
#include <string>
#include "Shader.h"

unsigned short Light::lights = 0;

Light::Light(vec3 pos, vec4 color, float range, float damper) : pos(pos), color(color), range(range), damper(damper) {
	if (lights >= MAX_LIGHTS) {
		printf("MAX_LIGHTS: %d\n", MAX_LIGHTS);
		return;
	}
	index = lights;
	lights++;

	sprintf(strPos, "light_pos[%d]", index);
	sprintf(strCol, "light_col[%d]", index);
	sprintf(strDamp, "light_damper[%d]", index);
	sprintf(strRange, "light_range[%d]", index);
}

Light::~Light() {}

void Light::render() {
	
	Shader::active->setVec2(strPos, pos.x, pos.y);
	Shader::active->setVec4(strCol, color);
	Shader::active->setFloat(strDamp, damper);
	Shader::active->setFloat(strRange, range);
	
}