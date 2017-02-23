#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <vector>



GLSLProgram::GLSLProgram():m_programID(0),m_vertexShaderID(0),m_fragmentShaderID(0),m_numAttributes(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	//Get a program object
	m_programID = glCreateProgram();
	//Create Shader
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0)
		fatalError("Vertex Shader failed to be created");

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0)
		fatalError("Fragment Shader failed to be created");

	//CompileShader
	compileShader(vertexShaderFilePath, m_vertexShaderID);
	compileShader(fragmentShaderFilePath, m_fragmentShaderID);

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
	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());	
}
void GLSLProgram::linkShaders()
{
	//Attach our shaders to our program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	//Link our program
	glLinkProgram(m_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(m_programID);
		//Don't leak shaders either.
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		//Use the infoLog as you see fit.
		fatalError("Shader failed to Link\n");
	}

	//Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::use()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}

}
void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}

}

GLint GLSLProgram::getUnifromLocation(const std::string& uniformName)
{
	GLint location=glGetUniformLocation(m_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		fatalError("Unifrom " + uniformName + " not found in shader");
	return location;
}
