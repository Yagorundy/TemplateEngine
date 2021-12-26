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
* <VariablesParser>
* 
* Reads and validates a list of values
*
*/

#pragma once

#include <string>

#include "../shared/variabletype.h"
#include "../storage/variablesstorage.h"
#include "../shared/stringhelper.h"

namespace TemplateEngine {
    class VariablesParser {
        const std::string _VAR_SEPARATOR;
        const std::string _NAME_TYPE_SEPARATOR;

        VariableType _getVarTypeFromString(const std::string& line, size_t l, size_t r);
        VariablesStorage::VariableData _parseNameTypeEntry(const std::string& line, size_t l, size_t r);

    public:
        VariablesParser(const std::string& varSparator, const std::string& nameTypeSeparator);
        VariablesStorage* parse(const std::string& line);
    };
}
