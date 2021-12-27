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
* <NestedComponent>
*
* A component that can contain multiple children (components)
* Returns the content of its children
*
*/

#pragma once

#include <vector>

#include "component.h"

namespace TemplateEngine {
	class NestedComponent : public Component {
		std::vector<const Component*> _components;

	public:
		NestedComponent();

		void addComponent(const Component& component);

		std::string generate(VariablesStorage&, ValuesStorage&) const;
		void pipe(VariablesStorage&, ValuesStorage&, std::ofstream&) const;

		~NestedComponent();
	};
}
