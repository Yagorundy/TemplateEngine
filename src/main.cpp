/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Yavor Tsankov
* @idnumber 0MI0600095
* @compiler GCC
*
* <main function>
*
*/

#include "templateengine.h"
#include "./shared/validationexception.h"

int main() {
	try {
		TemplateEngine::bootstrap();
	} catch (const TemplateEngine::ValidationException&) {
		return 1;
	}
	// TODO: add catch for std::exception
	catch (...) {
		// TODO: maybe output an error msg
		return 1;
	}
}
