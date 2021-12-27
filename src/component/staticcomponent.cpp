#include "staticcomponent.h"

namespace TemplateEngine {
	StaticComponent::StaticComponent(const std::string& text)
		: _TEXT(text)
	{ }

	std::string StaticComponent::generate(VariablesStorage&, ValuesStorage&) const {
		return this->_TEXT;
	}
}
