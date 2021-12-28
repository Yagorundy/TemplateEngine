#include "stringhelper.h"

namespace TemplateEngine {
	void trim(const std::string& str, size_t& l, size_t& r) {
		while (r > l && std::isspace(str[r - 1])) r--;
		while (std::isspace(str[l]) && r > l) l++;
	}

	bool isEmpty(const std::string& str) {
		if (str.empty())
			return true;
		for (size_t i = 0; i < str.size(); i++)
			if (!std::isspace(str[i]))
				return false;
		return true;
	}

	bool isValidVarName(const std::string& str, const size_t& l, const size_t& r) {
		if (str.empty())
			return false;
		for (size_t i = l; i < r; i++)
			if (!std::isalnum(str[i]) && str[i] != '_')
				return false;
		return true;
	}

	std::string substring(const std::string& str, const size_t& l, const size_t& r, const bool& trim) {
		if (trim) {
			auto i = l, j = r;
			TemplateEngine::trim(str, i, j);
			return str.substr(i, j - i);
		}
		return str.substr(l, r - l);
	}

	bool strEquals(const std::string& baseStr, const std::string lookupStr, const size_t& lookupIndex) {
		const auto maxCmpLen = lookupStr.size() - lookupIndex;
		if (maxCmpLen < baseStr.size()) return false;
		return baseStr.compare(0, baseStr.size(), lookupStr, lookupIndex, baseStr.size()) == 0;
	}
}
