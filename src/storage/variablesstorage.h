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
* <VariablesStorage>
* 
* Holds data about the values and contains methods for adding/retreiving the data.
*
*/

#pragma once

#include <string>
#include <vector>

#include "../shared/variabletype.h"
#include "../shared/validationexception.h"

namespace TemplateEngine {
    class VariablesStorage {
    public:
        struct VariableData {
            std::string name;
            VariableType type;
        };

    private:
        std::vector<VariableData> _variables;

    public:
        VariablesStorage();

        void addVariable(const VariableData& data);
        void removeVariable(const std::string& name);

        VariableType getTypeByName(const std::string& name) const;
        size_t getIndexByName(const std::string& name) const;
        std::string getNameByIndex(const size_t& index) const;
    };
}
