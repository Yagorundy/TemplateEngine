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
* <ValuesStorage>
* 
* Holds data about the variables and contains methods for adding/retreiving the data.
*
*/

#pragma once

#include <string>
#include <vector>

namespace TemplateEngine {
    class ValuesStorage {
    public:
        struct ValueData;

    private:
        std::vector<ValueData> _values;

    public:
        struct ValueData {
            std::string value;
            std::vector<std::string> values;
        };

        ValuesStorage();

        void addStringValue(const std::string& value);
        void addArrayValue(const std::vector<std::string> values);
        void removeValue(const size_t& index);

        const ValueData& getValue(size_t index) const;
    };
}
