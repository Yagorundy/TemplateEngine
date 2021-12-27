#include "component.h"

namespace TemplateEngine {
	void Component::pipe(VariablesStorage& variablesStorage, ValuesStorage& valuesStorage, std::ofstream& out) const {
		out << this->generate(variablesStorage, valuesStorage);
	}
}
