#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <vector>



GLSLProgram::GLSLProgram():_programID(0),_vertexShaderID(0),_fragmentShaderID(0),_numAttributes(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	//Get a program object
	_programID = glCreateProgram();
	//Create Shader
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
		fatalError("Vertex Shader failed to be created");

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
		fatalError("Fragment Shader failed to be created");

	//CompileShader
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);

	//LinkShader

}
void GLSLProgram::compileShader(const std::string& filePath,GLuint shaderID)
{
	//Load Shader
	std::ifstream file(filePath);
	if (file.fail())
		fatalError("Failed to open " + filePath);

	std::string fileContents = "";
	std::string line;
	while (std::getline(file, line))
	{
		fileContents += line + "\n";
	}

	file.close();

	//Source it
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);

	//Compile it
	glCompileShader(shaderID);

	//Error Checking
	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(shaderID); // Don't leak the shader.

		fatalError("Shader "+filePath+" failed to compile\n");
	}
}

void GLSLProgram::addAttribute(const std::string attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());	
}
void GLSLProgram::linkShaders()
{
	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//Use the infoLog as you see fit.
		fatalError("Shader failed to Link\n");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}

}
void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}

}

GLint GLSLProgram::getUnifromLocation(const std::string& uniformName)
{
	GLint location=glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		fatalError("Unifrom " + uniformName + " not found in shader");
	return location;
}
