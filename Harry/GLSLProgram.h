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
	GLuint m_programID;
	GLuint m_vertexShaderID,m_fragmentShaderID;
	int m_numAttributes;
};

