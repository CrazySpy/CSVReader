#include "CSVReader.h"

#include <iostream>

CSVReader::CSVReader(std::string filename,
                     bool header) : _csvFile(filename){
    if(!_csvFile.is_open()) throw "Failed to open the csv file.";

    try {
        if(header) {
            /*
             * If the csv file has a header, just parse it and store the parsed
             * header into the '_header' vector.
             */
            _header = _parseNext();
        }
    } catch(...) {
        throw "Failed to parse header line.";
    }
}

bool CSVReader::hasNext() {
    return _csvFile.good();
}

std::vector<std::string> CSVReader::getNextRecord() {
    return _parseNext();
}

std::vector<std::string> CSVReader::_parseNext() {
    std::vector<std::string> fields;

    bool solve = false;
    bool inQuote = false;
    char lastChar = '\0';

    int continuousQuoteCount = 0;

    std::string curField;
    while(!solve) {
        char ch = _csvFile.get();

        if(ch != '"' && continuousQuoteCount) {
            for(int i = 0; i < continuousQuoteCount / 2; ++i) {
                curField.push_back('"');
            }

            if(continuousQuoteCount % 2) {
                inQuote = false;
            }
            continuousQuoteCount = 0;
        }

        if(ch == '"' && !inQuote) {
            inQuote = true;
        } else if(ch == '"' && inQuote) {
            continuousQuoteCount++;
        } else if(ch == ',' && !inQuote) {
            fields.push_back(std::move(curField));
            curField.clear();
            inQuote = false;
        } else if(ch == ',' && inQuote) {
            if(lastChar != '"') {
                curField.push_back(ch);
            } else {
                fields.push_back(std::move(curField));
                curField.clear();
                inQuote = false;
            }
        } else if(ch == '\n' && inQuote) {
            curField.push_back(ch);
        } else if((ch == '\n' && !inQuote) || _csvFile.eof()) {
            fields.push_back(std::move(curField));
            curField.clear();
            inQuote = false;
            solve = true;
        } else {
            curField.push_back(ch);
        }

        lastChar = ch;
    }

    return fields;
}

std::vector<std::string> CSVReader::getHeader() {
    return _header;
}

void CSVReader::libTest() {
    std::cout << "Hello, World!" << std::endl;
}


