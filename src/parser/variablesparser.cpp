#include "variablesparser.h"

namespace TemplateEngine {
    VariablesParser::VariablesParser(const std::string& varSeparator, const std::string& nameTypeSeparator)
        : _VAR_SEPARATOR(varSeparator), _NAME_TYPE_SEPARATOR(nameTypeSeparator)
    { }

    VariableType TemplateEngine::VariablesParser::_getVarTypeFromString(const std::string& line, size_t l, size_t r) {
        trim(line, l, r);

        const auto len = r - l;
        if (strEquals("string*", line, l)) return VariableType::stringArray;
        if (strEquals("string", line, l)) return VariableType::string;
        throw ValidationException();
    }

    VariablesStorage::VariableData VariablesParser::_parseNameTypeEntry(const std::string& line, size_t l, size_t r) {
        size_t separatorIndex = -1;
        for (size_t i = l; i < r; i++) {
            if (strEquals(this->_NAME_TYPE_SEPARATOR, line, i)) {
                if (separatorIndex == -1)
                    separatorIndex = i;
                else
                    throw ValidationException();
            }
        }

        auto nameR = separatorIndex;
        trim(line, l, nameR);
        if (!isValidVarName(line, l, nameR) || l == nameR)
            throw ValidationException();
        const auto name = substring(line, l, nameR);

        const auto type = this->_getVarTypeFromString(line, separatorIndex + 1, r);

        return { name, type };
    }

    VariablesStorage* VariablesParser::parse(const std::string& line) {
        size_t l = 0, end = line.size();
        trim(line, l, end);
        size_t r = l;

        auto storage = new VariablesStorage();

        for (; r <= end; r++) {
            if (strEquals(this->_VAR_SEPARATOR, line, r) || r == end) {
                const auto& varData = this->_parseNameTypeEntry(line, l, r);
                storage->addVariable(varData);
                l = r + _VAR_SEPARATOR.size();
            }
        }

        return storage;
    }

}
