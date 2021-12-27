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
* <LoopComponent>
*
* Has the ability to run a loop (i.e. create a temporary new variable and execute the nested components for each value in the array of the loop)
*
*/

#pragma once

#include <string>

#include "nestedcomponent.h"

namespace TemplateEngine {
	class LoopComponent : public NestedComponent {
		const std::string _REF_VAR_NAME;
		const std::string _NEW_VAR_NAME;

	public:
		LoopComponent(const std::string& refVarName, const std::string& newVarName);

		std::string generate(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage) const;
		void pipe(VariablesStorage&, ValuesStorage&, std::ofstream&) const;
	};
}
