#include "templateparser.h"

namespace TemplateEngine {
	TemplateParser::TemplateParser(
		const std::string& varOpeningTag, const std::string& varClosingTag,
		const std::string& loopOpeningTag, const std::string& loopClosingTag,
		const std::string& loopDefinitionKeyword, const std::string& loopLookupKeyword, const std::string& loopEndKeyword
	) :
		_VAR_OPENING_TAG(varOpeningTag), _VAR_CLOSING_TAG(varClosingTag),
		_LOOP_OPENING_TAG(loopOpeningTag), _LOOP_CLOSING_TAG(loopClosingTag),
		_LOOP_DEFINITION_KEYWORD(loopDefinitionKeyword), _LOOP_LOOKUP_KEYWORD(loopLookupKeyword), _LOOP_END_KEYWORD(loopEndKeyword)
	{ }

	void TemplateParser::trimFrontUntilNewLineOrContent(const std::string& buffer, size_t& l) {
		while (std::isspace(buffer[l]) && buffer[l] != '\n') l++;
		if (buffer[l] == '\n') l++;
	}

	const StaticComponent* TemplateParser::_extractStaticComponent(const std::string& buffer, size_t l, const size_t& r) {
		// Replace \r\n with \n and \r with \n
		std::string result;
		for (size_t i = l; i <= r; i++) {
			if (i == r) {
				result += substring(buffer, l, i);
			} else if (buffer[i] == '\r') {
				result += substring(buffer, l, i);
				l = i + 1;

				// if not CRLF and only CR add new line
				bool isCrlfCombination = (i + 1) < r && buffer[i + 1] == '\n';
				if (!isCrlfCombination)
					result += '\n';
			}
		}

		return new const StaticComponent(result);
	}

	const VariableComponent* TemplateParser::_extractVariableComponent(const std::string& buffer, size_t l, size_t r) {
		trim(buffer, l, r);

		if (!isValidVarName(buffer, l, r))
			throw ValidationException();

		return new const VariableComponent(substring(buffer, l, r));
	}

	LoopComponent* TemplateParser::_extractLoopComponent(const std::string& buffer, size_t l, size_t r) {
		trim(buffer, l, r);

		size_t keywordIndex = 0;
		std::string refVarname, newVarName;
		// this flag is a bit ugly but it helps us move l and find end of keyword
		bool foundNonSpace = true;
		for (size_t i = l; i <= r; i++) {
			// space char or end of loop definition
			if (std::isspace(buffer[i]) || i == r) {
				// FIRST space char or end of loop definition
				if (!foundNonSpace || i == r) {
					foundNonSpace = true;

					// Loop definition validation
					if (keywordIndex == 0 && !strEquals(this->_LOOP_DEFINITION_KEYWORD, buffer, l))
						throw ValidationException();
					else if (keywordIndex == 1)
						newVarName = substring(buffer, l, i);
					else if (keywordIndex == 2 && !strEquals(this->_LOOP_LOOKUP_KEYWORD, buffer, l))
						throw ValidationException();
					else if (keywordIndex == 3)
						refVarname = substring(buffer, l, i);
					else if (keywordIndex > 3)
						throw ValidationException();

					keywordIndex++;
				}
			}
			else {
				// fisrt non space char -> move l to start of word
				if (foundNonSpace)
					l = i;
				foundNonSpace = false;
			}
		}
		// not enough keywords
		if (keywordIndex <= 3)
			throw ValidationException();

		return new LoopComponent(refVarname, newVarName);
	}

	const NestedComponent* TemplateParser::parse(const std::string templatePath) {
		std::ifstream file(templatePath, std::ifstream::binary);
		if (!file.is_open())
			throw ValidationException();

		std::string buffer;

		// a vector containing all nested components
		// when starting a loop add new nested component to the end and when exiting a loop remove the last component
		// always write to the innermost component
		std::vector<NestedComponent*> components;
		components.push_back(new NestedComponent());

		bool inVariable = false,
			inLoopStatement = false,
			isLoopTrimmed = false;
		while (!file.eof()) {
			// add read content to the buffer
			char* readBuffer = new char[this->_BUFFER_LEN];
			file.read(readBuffer, this->_BUFFER_LEN);
			buffer.append(readBuffer, file.gcount());
			delete[] readBuffer;

			size_t l = 0, r = 0;
			for (; r <= buffer.size(); r++) {
				if (strEquals(this->_VAR_OPENING_TAG, buffer, r)) {
					// Double var declaration
					if (inVariable)
						throw ValidationException();
					inVariable = true;

					// Trim first new line of first static content in loop
					if (!isLoopTrimmed) {
						this->trimFrontUntilNewLineOrContent(buffer, l);
						isLoopTrimmed = true;
					}

					components.back()->addComponent(*this->_extractStaticComponent(buffer, l, r));
					l = r + this->_VAR_OPENING_TAG.size();
				}
				else if (strEquals(this->_VAR_CLOSING_TAG, buffer, r)) {
					// No opening tag
					if (!inVariable)
						throw ValidationException();
					inVariable = false;

					components.back()->addComponent(*this->_extractVariableComponent(buffer, l, r));
					l = r + this->_VAR_CLOSING_TAG.size();
				}
				else if (strEquals(this->_LOOP_OPENING_TAG, buffer, r)) {
					// No loop inside variable and no double opening loop tag
					if (inVariable || inLoopStatement)
						throw ValidationException();
					inLoopStatement = true;

					components.back()->addComponent(*this->_extractStaticComponent(buffer, l, r));
					l = r + this->_LOOP_OPENING_TAG.size();
				}
				else if (strEquals(this->_LOOP_CLOSING_TAG, buffer, r)) {
					// No opening tag
					if (!inLoopStatement)
						throw ValidationException();
					inLoopStatement = false;

					auto i = l, j = r;
					trim(buffer, i, j);
					const auto isLoopEnd = strEquals(this->_LOOP_END_KEYWORD, buffer, i);

					if (isLoopEnd) {
						const auto loopComponent = components.back();
						components.pop_back();
						components.back()->addComponent(*loopComponent);
					} else {
						components.push_back(this->_extractLoopComponent(buffer, i, j));
						isLoopTrimmed = false;
					}

					l = r + this->_LOOP_CLOSING_TAG.size();
				}
				else if (file.eof() && r == buffer.size() && l < r) {
					components.back()->addComponent(*this->_extractStaticComponent(buffer, l, r));
				}
			}

			// preserve only unprocessed template content 
			if (l < buffer.size() && l != 0)
				buffer = substring(buffer, l, buffer.size());
			// if no unprocessed template content reset the buffer
			else
				buffer = "";
		}
		// trailing opening tag
		if (inVariable || inLoopStatement)
			throw ValidationException();

		file.close();
		return components.front();
	}
}
