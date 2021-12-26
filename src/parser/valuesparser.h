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
* <ValuesParser>
* 
* Reads and validates a list of variables
* 
*/

#pragma once

#include <string>

#include "../storage/valuesstorage.h"

namespace TemplateEngine {
    class ValuesParser {
        const std::string _SEPARATOR;
        const std::string _ARR_OPENING_TAG;
        const std::string _ARR_CLOSING_TAG;

    public:
        ValuesParser(const std::string& separator, const std::string& arrOpeningTag, const std::string& arrClosingTag);
        ValuesStorage* parse(const std::string& line);
    };
}
