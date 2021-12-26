#include "valuesparser.h"

namespace TemplateEngine {
    ValuesParser::ValuesParser(const std::string& separator, const std::string& arrOpeningTag, const std::string& arrClosingTag)
        : _SEPARATOR(separator), _ARR_OPENING_TAG(arrOpeningTag), _ARR_CLOSING_TAG(arrClosingTag)
    { }

    std::vector<std::string> ValuesParser::_parseArray(const std::string& line, std::size_t l, std::size_t r) {
        while (!strEquals(this->_ARR_OPENING_TAG, line, l)) l++;
        l += this->_ARR_OPENING_TAG.size();
        while (!strEquals(this->_ARR_CLOSING_TAG, line, r)) r--;

        std::vector<std::string> values;

        for (auto i = l; i <= r; i++) {
            if (strEquals(this->_SEPARATOR, line, i) || i == r) {
                values.push_back(substring(line, l, i, true));
                l = i + this->_SEPARATOR.size();
            }
        }

        return values;
    }

    ValuesStorage* ValuesParser::parse(const std::string& line, const VariablesStorage& variablesStorage) {
        size_t l = 0, end = line.size();
        trim(line, l, end);
        size_t r = l;

        auto valuesStorage = new ValuesStorage();

        size_t valIndex = 0;
        bool inArray = false, currValueIsArray = false;
        for (; r <= end; r++) {
            if (strEquals(this->_ARR_OPENING_TAG, line, r)) {
                // Multiple opening symbols
                if (currValueIsArray)
                    throw ValidationException();
                inArray = true;
                currValueIsArray = true;
            }
            else if (strEquals(this->_ARR_CLOSING_TAG, line, r)) {
                // Double closing symbol or closing symbol without opening symbol
                if (!inArray)
                    throw ValidationException();
                inArray = false;
            }
            else if ((strEquals(this->_SEPARATOR, line, r) && !inArray) || r == end) {
                // Last value and no closing array symbol
                if (currValueIsArray && inArray)
                    throw ValidationException();

                // Type validation
                const auto& type = variablesStorage.getTypeByName(variablesStorage.getNameByIndex(valIndex));
                if ((type == VariableType::string && currValueIsArray) || (type == VariableType::stringArray && !currValueIsArray))
                    throw ValidationException();

                if (currValueIsArray)
                    valuesStorage->addArrayValue(this->_parseArray(line, l, r));
                else
                    valuesStorage->addStringValue(substring(line, l, r, true));
                valIndex++;

                l = r + this->_SEPARATOR.size();
                currValueIsArray = false;
            }
        }

        return valuesStorage;
    }
}


