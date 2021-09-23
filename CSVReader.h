#ifndef CSVREADER_LIBRARY_H
#define CSVREADER_LIBRARY_H
#include <iostream>
#include <vector>
#include <fstream>

class CSVReader {
public:
    CSVReader(std::string filename, bool header = true);

    /*
     * Check whether CSV file has next record.
     */
    bool hasNext();

    std::vector<std::string> getNextRecord();

    std::vector<std::string> getHeader();

    /*
     * If the program calls libTest successfully, it means the library is
     * configured properly.
     */
    void libTest();

private:
    std::ifstream _csvFile;
    std::vector<std::string> _header;

    unsigned int _columnNum = 0;
    std::vector<std::string> _nextLine;

    /*
     * Due to both of header and record have the same style,
     * the function can parse both of header and record.
     */
    std::vector<std::string> _parseNext();
};

#endif //CSVREADER_LIBRARY_H
