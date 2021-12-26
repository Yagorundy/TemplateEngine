#include "variablesstorage.h"

namespace TemplateEngine {
	VariablesStorage::VariablesStorage()
		: _variables(std::vector<VariableData>())
	{ }

	void VariablesStorage::addVariable(const VariableData& data) {
		if (this->getIndexByName(data.name) != -1)
			throw ValidationException();
		this->_variables.push_back(data);
	}

	void VariablesStorage::removeVariable(const std::string& name) {
		this->_variables.erase(this->_variables.begin() + this->getIndexByName(name));
	}

	VariableType VariablesStorage::getTypeByName(const std::string& name) const {
		const auto& index = this->getIndexByName(name);
		return index == -1 ? VariableType::undefined : this->_variables[index].type;
	}

	size_t VariablesStorage::getIndexByName(const std::string& name) const {
		for (size_t i = 0; i < this->_variables.size(); i++)
			if (this->_variables[i].name == name)
				return i;
		return -1;
	}

	std::string VariablesStorage::getNameByIndex(const size_t& index) const {
		return this->_variables[index].name;
	}
}
