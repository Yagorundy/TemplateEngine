#include "loopcomponent.h"

namespace TemplateEngine {
	LoopComponent::LoopComponent(const std::string& refVarName, const std::string& newVarName)
		: _REF_VAR_NAME(refVarName), _NEW_VAR_NAME(newVarName)
	{ }

	std::string LoopComponent::generate(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage) const {
		const auto& index = variablesStorage.getIndexByName(this->_REF_VAR_NAME);
		const std::vector<std::string> values = valuesStorage.getValue(index).values;
		
		std::string result = "";
		variablesStorage.addVariable({ _NEW_VAR_NAME, VariableType::string });
		for (size_t i = 0; i < values.size(); i++) {
			valuesStorage.addStringValue(values[i]);

			result += NestedComponent::generate(variablesStorage, valuesStorage);

			const auto& newValIndex = variablesStorage.getIndexByName(_NEW_VAR_NAME);
			valuesStorage.removeValue(newValIndex);
		}
		variablesStorage.removeVariable(_NEW_VAR_NAME);

		return result;
	}

	void LoopComponent::pipe(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage, std::ofstream& out) const {
		const auto& index = variablesStorage.getIndexByName(this->_REF_VAR_NAME);
		const std::vector<std::string> values = valuesStorage.getValue(index).values;

		variablesStorage.addVariable({ _NEW_VAR_NAME, VariableType::string });
		for (size_t i = 0; i < values.size(); i++) {
			valuesStorage.addStringValue(values[i]);

			NestedComponent::pipe(variablesStorage, valuesStorage, out);

			const auto& newValIndex = variablesStorage.getIndexByName(_NEW_VAR_NAME);
			valuesStorage.removeValue(newValIndex);
		}
		variablesStorage.removeVariable(_NEW_VAR_NAME);
	}
}
