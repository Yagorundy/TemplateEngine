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
* <StaticComponent>
*
* A basic component that returns a string
*
*/

#pragma once

#include <string>

#include "component.h"

namespace TemplateEngine {
	class StaticComponent : public Component {
		const std::string _TEXT;
	public:
		StaticComponent(const std::string& text);
		std::string generate(VariablesStorage&, ValuesStorage&) const;
	};
}
