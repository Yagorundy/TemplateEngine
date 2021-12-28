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
* <TemplateParser>
* 
* Reads and validates the template file
* Constructs the template components
*
*/

#pragma once

#include <string>

#include "../shared/validationexception.h"
#include "../shared/stringhelper.h"
#include "../component/staticcomponent.h"
#include "../component/variablecomponent.h"
#include "../component/loopcomponent.h"

namespace TemplateEngine {
	class TemplateParser {
		static const auto _BUFFER_LEN = 1024;

		const std::string _VAR_OPENING_TAG;
		const std::string _VAR_CLOSING_TAG;

		const std::string _LOOP_OPENING_TAG;
		const std::string _LOOP_CLOSING_TAG;

		const std::string _LOOP_DEFINITION_KEYWORD;
		const std::string _LOOP_LOOKUP_KEYWORD;
		const std::string _LOOP_END_KEYWORD;

		void trimFrontUntilNewLineOrContent(const std::string& buffer, size_t& l);
		
		const StaticComponent* _extractStaticComponent(const std::string& buffer, size_t l, const size_t& r);
		const VariableComponent* _extractVariableComponent(const std::string& buffer, size_t l, size_t r);
		LoopComponent* _extractLoopComponent(const std::string& buffer, size_t l, size_t r);

	public:
		TemplateParser(
			const std::string& varOpeningTag, const std::string& varClosingTag,
			const std::string& loopOpeningTag, const std::string& loopClosingTag,
			const std::string& loopDefinitionKeyword, const std::string& loopLookupKeyword, const std::string& loopEndKeyword
		);

		const NestedComponent* parse(const std::string templatePath);
	};
}
