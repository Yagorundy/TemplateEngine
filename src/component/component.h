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
* <Component>
* 
* The logical part of a template
* Each component can return static or computed content
* 
*/

#pragma once

#include <string>
#include <fstream>

#include "../storage/variablesstorage.h"
#include "../storage/valuesstorage.h"

namespace TemplateEngine {
	class Component {
	public:
		// compute the value using the variable and value datas
		virtual std::string generate(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage) const = 0;
		// ability to straight up write the result to a file (useful optimization when having children components)
		virtual void pipe(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage, std::ofstream& out) const;
	};
}
