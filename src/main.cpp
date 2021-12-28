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

int main() {
	try {
		TemplateEngine::bootstrap();
	}
	// ugly catch but it must be this way because of project requirements
	catch (...) {
		return 1;
	}
}
