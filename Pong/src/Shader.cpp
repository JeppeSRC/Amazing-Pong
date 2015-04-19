#include "Shader.h"
#include <glew.h>
#include <stdio.h>
#include <string>


#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

Shader* Shader::active;

#pragma region stuff

unsigned int LoadShader(const char* vert, const char* frag);
bool error(unsigned int shader, bool program, int param);
std::string LoadFile(const char* filename);


Shader::Shader(const char* vert, const char* frag, bool src){
	if (src){
		shader = LoadShader(vert, frag);
	}
	else{
		shader = LoadShader(LoadFile(vert).c_str(), LoadFile(frag).c_str());
	}
}

unsigned int LoadShader(const char* vert, const char* frag){
	unsigned int program = glCreateProgram();
	unsigned int v = glCreateShader(GL_VERTEX_SHADER);
	unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(v, 1, &vert, NULL);
	glShaderSource(f, 1, &frag, NULL);

	glCompileShader(v);

	if (error(v, false, GL_COMPILE_STATUS)){
		glDeleteShader(v);
		glDeleteShader(f);
		glDeleteProgram(program);
		return -1;
	}

	glCompileShader(f);

	if (error(f, false, GL_COMPILE_STATUS)){
		glDeleteShader(v);
		glDeleteShader(f);
		glDeleteProgram(program);
		return -1;
	}

	glAttachShader(program, v);
	glAttachShader(program, f);

	glLinkProgram(program);
		
	if (error(program, true, GL_LINK_STATUS)){
		glDeleteShader(v);
		glDeleteShader(f);
		glDeleteProgram(program);
		return -1;
	}

	glValidateProgram(program);

	if (error(program, true, GL_VALIDATE_STATUS)){
		glDeleteShader(v);
		glDeleteShader(f);
		glDeleteProgram(program);
		return -1;
	}

	glDeleteShader(v);
	glDeleteShader(f);

	return program;
}

bool error(unsigned int shader, bool program, int param){
	char* log;
	int res, length;

	if (!program){
		glGetShaderiv(shader, param, &res);
		if (res == GL_FALSE) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			log = new char[length];
			glGetShaderInfoLog(shader, 2048, &length, log);
			printf("SHADER ERROR: %s\n", log);
			delete[] log;
			return true;
		}
	}
	else{
		glGetProgramiv(shader, param, &res);
		if (res == GL_FALSE){
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
			log = new char[length];
			glGetProgramInfoLog(shader, 2048, &length, log);
			printf("PROGRAM ERROR: %s\n", log);
			delete[] log;
			return true;
		}
	}

	return false;
}

std::string LoadFile(const char* filename){
	
	FILE* file;
	fopen_s(&file, filename, "rt");

	if (!file){
		printf("Faild To Open File: %s\n", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data = new char[length + 1];
	memset(data, 0, length + 1);

	fread_s(data, length + 1, length + 1, 1, file);

	fclose(file);

	return std::string(data);
}

void Shader::bind(){
	glUseProgram(shader);
	active = this;
}

Shader::~Shader(){
	glDeleteProgram(shader);
}

#pragma endregion

#pragma region uniform stuff

unsigned int Shader::getUniformLocation(const char* name){
	if (uniformCache.find(name) != uniformCache.end()){
		return uniformCache[name];
	}

	unsigned int loc = glGetUniformLocation(shader, name);
	if (loc != -1)
		uniformCache[name] = loc;

	return loc;
}

void Shader::setFloat(const char* name, float v){
	glUniform1f(getUniformLocation(name), v);
}

void Shader::setInt(const char* name, int v){
	glUniform1i(getUniformLocation(name), v);
}

void Shader::setVec2(const char* name, float x, float y){
	glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const char* name, float x, float y, float z){
	glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec3(const char* name, const vec3& v){
	glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void Shader::setVec4(const char* name, float x, float y, float z, float w){
	glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setVec4(const char* name, const vec4& v) {
	glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::setMat4(const char* name, const mat4& m){
	glUniformMatrix4fv(getUniformLocation(name), 1, false, m.toArray());
}

#pragma endregion
