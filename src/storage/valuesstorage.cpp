#include "valuesstorage.h"

namespace TemplateEngine {
	ValuesStorage::ValuesStorage()
		: _values(std::vector<ValueData>())
	{ }

	void ValuesStorage::addStringValue(const std::string& value) {
		this->_values.push_back({ value });
	}

	void ValuesStorage::addArrayValue(std::vector<std::string> values) {
		this->_values.push_back({ "", values });
	}

	void ValuesStorage::removeValue(const size_t& index) {
		this->_values.erase(this->_values.begin() + index);
	}

	const ValuesStorage::ValueData& ValuesStorage::getValue(size_t index) const {
		return this->_values[index];
	}
}
