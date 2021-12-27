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
* <VariableComponent>
*
* A component that returns the value of a variable
*
*/

#pragma once

#include <string>

#include "component.h"

namespace TemplateEngine {
	class VariableComponent : public Component {
		const std::string _VAR_NAME;
	public:
		VariableComponent(const std::string& varName);
		std::string generate(VariablesStorage&, ValuesStorage&) const;
	};
}
