#pragma once
#include "vec3.h"
#include "vec4.h"
#include "Texture.h"

class Renderable {
protected:
	vec3 size;
	vec3 pos;
	Texture* texture;
	vec4 color;
	
public:
	Renderable(const vec3 pos, const vec3 size);
	virtual ~Renderable();

	virtual void update();
	virtual void render();

	inline vec3& getPos() { return pos; }
	inline vec3& getSize() { return size; }
	inline Texture* getTexture() const { return texture; }
	inline vec4& getColor() { return color; }
	inline void setPos(const vec3& pos) { this->pos = pos; }
	inline void setSize(const vec3& size) { this->size = size; }
	inline void setTexture(Texture* texture) { this->texture = texture; }
	inline void setColor(const vec4& color) { this->color = color; }
};
