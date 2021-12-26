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
* Helper methods to work with strings
*
*/

#pragma once

#include <string>

namespace TemplateEngine {
	// Moves l and r until they no longer point to a space character
	void trim(const std::string& str, size_t& l, size_t& r);

	// Checks if string includes only space characters
	bool isEmpty(const std::string& str);

	// [A-Za-z0-9_]+
	bool isValidVarName(const std::string& str, const size_t& l, const size_t& r);

	// Substring method that uses l and r instead of offset and len and has the ability to trim the result
	std::string substring(const std::string& str, const size_t& l, const size_t& r, const bool& trim = false);

	// Checks whether baseStr is identical to a substring from lookupStr with the same length as baseStr and starting from lookupIndex
	// strEquals("xx", "123xx56", 3) -> true
	// strEquals("xx", "123xx56", 2) -> false
	// strEquals("xx", "123xx56", 4) -> false
	bool strEquals(const std::string& baseStr, const std::string lookupStr, const size_t& lookupIndex);
}
