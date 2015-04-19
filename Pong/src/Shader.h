#pragma once
#include <map>


class vec3;
class vec4;
class mat4;

class Shader{
public:
	Shader(const char* vert, const char* frag, bool src = false);
	~Shader();

	void bind();

	static Shader* active;

public:
	unsigned int getUniformLocation(const char* name);
	void setFloat(const char* name, float v);
	void setInt(const char* name, int v);
	void setVec2(const char* name, float x, float y);
	void setVec3(const char* name, float x, float y, float z);
	void setVec3(const char* name, const vec3& v);
	void setVec4(const char* name, float x, float y, float z, float w);
	void setVec4(const char* name, const vec4& color);
	void setMat4(const char* name, const mat4& m);

	
private:
	std::map<const char*, unsigned int> uniformCache;
	unsigned int shader;
};

