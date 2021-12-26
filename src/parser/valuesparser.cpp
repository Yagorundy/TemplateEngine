#include "valuesparser.h"

TemplateEngine::ValuesParser::ValuesParser(const std::string& separator, const std::string& arrOpeningTag, const std::string& arrClosingTag)
    : _SEPARATOR(separator), _ARR_OPENING_TAG(arrOpeningTag), _ARR_CLOSING_TAG(arrClosingTag)
{ }

TemplateEngine::ValuesStorage* TemplateEngine::ValuesParser::parse(const std::string& line) {
    // TODO
}
