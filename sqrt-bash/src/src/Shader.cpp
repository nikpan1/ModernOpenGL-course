#include "Shader.h"

Shader::Shader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

Shader::~Shader()
{
	Shader::Clear();
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
    Shader::Compile(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);
	if (!fileStream.is_open()) {
		printf("Failed to open a file %s", fileLocation);
		return "";
	}
	
	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	
	fileStream.close();

	return content;
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexStr = Shader::ReadFile(vertexLocation);
	std::string fragmentStr = Shader::ReadFile(fragmentLocation);
	const char* vertexCode = vertexStr.c_str();
	const char* fragmentCode = fragmentStr.c_str();
	Shader::Compile(vertexCode, fragmentCode);
}

void Shader::Use() {
	glUseProgram(shaderID);
}

void Shader::Clear() {
	if (shaderID) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
}

GLuint Shader::GetProjectionLocation()
{
    return uniformProjection;
}

GLuint Shader::GetModelLocation()
{
    return uniformModel;
}

GLuint Shader::GetViewLocation()
{
    return uniformView;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColorLocation()
{
	return uniformAmbientColor;
}

GLuint Shader::GetDiffusionIntensityLocation()
{
	return uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return uniformDirection;
}

GLuint Shader::GetSpecularDensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
	return uniformShininess;
}

GLuint Shader::GetEyePosition()
{
	return uniformEyePosition;
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	
	if (!shaderID) {
		printf("shader error");
		return;
	}

	Shader::Add(shaderID, vertexCode, GL_VERTEX_SHADER);
	Shader::Add(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("link shader error \n%s\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("link shader error \n%s\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");

	uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");

	uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
	uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");

	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");

}



void Shader::Add(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// 		shaderType	0x00008b31	VERT
	//					0x00008B30	FRAG	35632 	
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("compile shader error[%d] \n%s\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);

}
