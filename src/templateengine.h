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
* <TemplateEngine::bootstrap>
* 
* 1. Reads the paths to the template file and the data file
* 2. Parses and validates the data
* 3. Parses and validates the template and creates the template components
* 4. Uses the template components to build and output the reult
* 
*/

#pragma once

#include <fstream>

#include "shared/validationexception.h"
#include "shared/stringhelper.h"
#include "parser/variablesparser.h"
#include "parser/valuesparser.h"
#include "parser/templateparser.h"

namespace TemplateEngine {
	void bootstrap();
}
