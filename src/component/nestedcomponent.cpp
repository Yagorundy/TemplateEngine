#include "nestedcomponent.h"

namespace TemplateEngine {
	NestedComponent::NestedComponent()
		: _components(std::vector<const Component*>())
	{ }

	void NestedComponent::addComponent(const Component& component) {
		this->_components.push_back(&component);
	}

	std::string NestedComponent::generate(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage) const {
		std::string result = "";
		for (const auto& component : this->_components)
			result += component->generate(variablesStorage, valuesStorage);
		return result;
	}

	void NestedComponent::pipe(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage, std::ofstream& out) const {
		for (const auto& component : this->_components)
			out << component->generate(variablesStorage, valuesStorage);
	}

	NestedComponent::~NestedComponent() {
		for (const auto& component : this->_components) {
			delete component;
		}
	}
}
