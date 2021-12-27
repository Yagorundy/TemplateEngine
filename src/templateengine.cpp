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
        std::unique_ptr<VariablesStorage> variablesStorage(variablesParser.parse(line));

        ValuesParser valuesParser(",", "{", "}");
        std::vector<ValuesStorage*> valuesStorages;
        while (std::getline(dataFile, line)) {
            if (!isEmpty(line)) {
                valuesStorages.push_back(valuesParser.parse(line, *variablesStorage));
            }
        }

        TemplateParser templateParser("{{", "}}", "{%", "%}", "for", "in", "endfor");
        std::unique_ptr<const NestedComponent> rootComponent(templateParser.parse(templateFilePath));
        
        for (size_t i = 0; i < valuesStorages.size(); i++) {
            const std::string name = std::to_string(i + 1) + ".txt";
            const std::string path = "./results/" + name;

            std::ofstream out(path);
            if (!out.is_open())
                throw ValidationException();

            rootComponent->pipe(*variablesStorage, *valuesStorages[i], out);
            out.close();
        }

        for (const auto& valuesStorage : valuesStorages) {
            printf(rootComponent->generate(*variablesStorage, *valuesStorage).c_str());
            printf("\n\n");
        }

        for (const auto& valuesStorage : valuesStorages)
            delete valuesStorage;
    }
}
