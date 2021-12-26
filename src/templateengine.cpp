#include "templateengine.h"

namespace TemplateEngine {
    void bootstrap() {
        // TODO: remove hardcode
        const auto databaseFilePath = "./data/data_spaced.txt";
        const auto templateFilePath = "./data/template.txt";

        std::ifstream dataFile(databaseFilePath, std::ifstream::binary);
        if (!dataFile.is_open())
            throw ValidationException();

        std::string line;
        do {
            std::getline(dataFile, line);
        } while (!dataFile.eof() && isEmpty(line));

        VariablesParser variablesParser(",", ":");
        std::unique_ptr<const VariablesStorage> variablesStorage(variablesParser.parse(line));

        ValuesParser valuesParser(",", "{", "}");
        std::vector<const ValuesStorage*> valuesStorages;
        while (std::getline(dataFile, line)) {
            if (!isEmpty(line)) {
                valuesStorages.push_back(valuesParser.parse(line, *variablesStorage));
            }
        }
    }
}
