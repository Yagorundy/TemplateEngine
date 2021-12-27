#include "variablecomponent.h"

namespace TemplateEngine {
	VariableComponent::VariableComponent(const std::string& varName)
		: _VAR_NAME(varName)
	{ }

	std::string VariableComponent::generate(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage) const {
		const auto& index = variablesStorage.getIndexByName(this->_VAR_NAME);
		if (index == -1)
			return "";
		return valuesStorage.getValue(index).value;
	}
}
