#include "shaderCompiler.h"
#include "file.h"

GLuint compileShaders()
{
	GLchar *vertexsource, *fragmentsource; // �ҽ��ڵ����庯��
	GLuint vertexshader, fragmentshader; // ���̴�

	vertexsource = filetobuf("vertex.glvs");
	fragmentsource = filetobuf("fragment.glfs");

	//---���ؽ� ���̴� ��ü ����� 
	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	// ���̴��ڵ带 ���̴� ��ü�� �ֱ�: GL�� ��������. (�ҽ��ڵ�: ���ڿ�) 
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	// ���ؽ� ���̴� �������ϱ� 
	glCompileShader(vertexshader);

	// �������� ����� ���� ���� ���: ���� üũ 
	GLint IsCompiled_VS;
	GLint maxLength;
	GLchar * vertexInfoLog;

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);

	if (IsCompiled_VS == false) {
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);
		vertexInfoLog = (char *)malloc(maxLength);
		glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
		free(vertexInfoLog);
		return false;
	}

	//---�����׸�Ʈ ���̴� ��ü ����� 
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ڵ带 ���̴� ��ü�� �ֱ�: GL�� ��������. 
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	// �����׸�Ʈ ���̴� ������ 
	glCompileShader(fragmentshader);

	// �������� ����� ���� ���� ���: ������ ���� üũ	
	GLint IsCompiled_FS;
	GLchar * fragmentInfoLog;

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);

	if (IsCompiled_FS == false) {
		glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);
		fragmentInfoLog = (char *)malloc(maxLength);
		glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
		free(fragmentInfoLog);
		return false;
	}

	GLuint ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, vertexshader);
	glAttachShader(ShaderProgramID, fragmentshader);

	// in_Position: �ε��� 0, 
	// in_Color: �ε��� 1���� �Ӽ� �ε����� ���ε��Ѵ�. 
	// �Ӽ���ġ�� ���α׷� ��ũ ���� �����Ѵ�.
	glBindAttribLocation(ShaderProgramID, 0, "in_Position");
	glBindAttribLocation(ShaderProgramID, 1, "in_Color");

	// ���α׷���ũ 
	// �̶�, ���̴� ���α׷��� �������� ���̳ʸ��ڵ尡 ���̴������Ͽ� 
	// �����ǰ� ���ڵ尡 GPU�� ���ε�� (���������ٸ�) 
	glLinkProgram(ShaderProgramID);

	GLint IsLinked;
	GLchar * shaderProgramInfoLog;

	// ��ũ�� �Ǿ����� üũ�ϱ� 
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, (int *)&IsLinked);

	if (IsLinked == false) {
		glGetProgramiv(ShaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);
		shaderProgramInfoLog = (char *)malloc(maxLength);
		glGetProgramInfoLog(ShaderProgramID, maxLength, &maxLength, shaderProgramInfoLog);
		free(shaderProgramInfoLog);
		return false;
	}
	return ShaderProgramID;
}