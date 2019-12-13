#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <atlfile.h>

int loadObj(const char* filename, std::vector< glm::vec3 > &vertex, std::vector< glm::vec3 > &normal);