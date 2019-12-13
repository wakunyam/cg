#include "shaderCompiler.h"
#include "file.h"

GLuint compileShaders()
{
	GLchar *vertexsource, *fragmentsource; // 소스코드저장변수
	GLuint vertexshader, fragmentshader; // 세이더

	vertexsource = filetobuf("vertex.glvs");
	fragmentsource = filetobuf("fragment.glfs");

	//---버텍스 세이더 객체 만들기 
	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	// 세이더코드를 세이더 객체에 넣기: GL로 보내진다. (소스코드: 문자열) 
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	// 버텍스 세이더 컴파일하기 
	glCompileShader(vertexshader);

	// 컴파일이 제대로 되지 않은 경우: 에러 체크 
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

	//---프래그먼트 세이더 객체 만들기 
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	// 세이더 코드를 세이더 객체에 넣기: GL로 보내진다. 
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	// 프래그먼트 세이더 컴파일 
	glCompileShader(fragmentshader);

	// 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크	
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

	// in_Position: 인덱스 0, 
	// in_Color: 인덱스 1으로 속성 인덱스를 바인드한다. 
	// 속성위치는 프로그램 링크 전에 수행한다.
	glBindAttribLocation(ShaderProgramID, 0, "in_Position");
	glBindAttribLocation(ShaderProgramID, 1, "in_Color");

	// 프로그램링크 
	// 이때, 세이더 프로그램은 에러없이 바이너리코드가 세이더를위하여 
	// 생성되고 그코드가 GPU에 업로드됨 (에러가없다면) 
	glLinkProgram(ShaderProgramID);

	GLint IsLinked;
	GLchar * shaderProgramInfoLog;

	// 링크가 되었는지 체크하기 
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