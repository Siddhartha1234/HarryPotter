#pragma once
#include <string>
#include <GL/glew.h>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void addAttribute(const std::string attributeName);
	void linkShaders();
	void use();
	void unuse();

	GLint getUnifromLocation(const std::string& uniformName);

private:
	void compileShader(const std::string& filePath, GLuint shaderID);
	GLuint _programID;
	GLuint _vertexShaderID,_fragmentShaderID;
	int _numAttributes;
};

