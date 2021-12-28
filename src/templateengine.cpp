#include "templateengine.h"

namespace TemplateEngine {
    const unsigned int MAX_FILE_PATH_SIZE = 256;
    void bootstrap() {
        char dataFilePath[MAX_FILE_PATH_SIZE], templateFilePath[MAX_FILE_PATH_SIZE];
        printf("Enter path to template file: ");
        scanf_s("%s", templateFilePath, MAX_FILE_PATH_SIZE);
        printf("Enter path to data file: ");
        scanf_s("%s", dataFilePath, MAX_FILE_PATH_SIZE);

        std::ifstream dataFile(dataFilePath, std::ifstream::binary);
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

        for (const auto& valuesStorage : valuesStorages)
            delete valuesStorage;        
    }
}
