#include "variablesparser.h"

TemplateEngine::VariablesParser::VariablesParser(const std::string& varSeparator, const std::string& nameTypeSeparator)
    : _VAR_SEPARATOR(varSeparator), _NAME_TYPE_SEPARATOR(nameTypeSeparator)
{ }

TemplateEngine::VariablesStorage* TemplateEngine::VariablesParser::parse(const std::string& line) {
    // TODO
}
