#include "camera.h"

void cameraSetting(GLuint shaderprogram, bool topView)
{
	// ºäÀ× º¯È¯
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;

	glm::mat4 view = glm::mat4(1.0f);

	if (topView) {
		cameraPos = glm::vec3(0, 0.f, 1000.0f);
		cameraDirection = glm::vec3(0, 0, 0.f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		cameraPos = glm::vec3(0, 0, 0 +3.0f);
		cameraDirection = glm::vec3(0, 0, 0.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(shaderprogram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	// Åõ¿µ º¯È¯
	glm::mat4 projection = glm::mat4(1.0f);

	if (topView) {
		projection = glm::ortho(-400.0f,400.0f, -500.0f, 500.0f, 0.0001f, 10000.0f);
	}
	else {
		projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)1000, 0.1f, 50.0f);
	}

	unsigned int projectionLocation = glGetUniformLocation(shaderprogram, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
