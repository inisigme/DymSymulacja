#include "wszystko.h"
#include <string>
#include <iostream>

void blad(std::string f, int l) {

	for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
		std::cout << f << "   -   " << l << "   -   ";
		switch (err) {
		case(GL_INVALID_ENUM):
			std::cout << "GL_INVALID_ENUM";
			break;
		case(GL_INVALID_OPERATION):
			std::cout << "GL_INVALID_OPERATION ";
			break;
		case(GL_INVALID_VALUE):
			std::cout << "GL_INVALID_VALUE ";
			break;
		default:
			std::cout << err;
		}
		std::cout << std::endl;
		getchar();
	}
}