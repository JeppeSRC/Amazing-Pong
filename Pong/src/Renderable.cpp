#include "Renderable.h"


Renderable::Renderable(const vec3 pos, const vec3 size) : pos(pos), size(size) {}
Renderable::~Renderable() {
	if (texture) delete texture;
}

void Renderable::update() {

}

void Renderable::render() {

}


