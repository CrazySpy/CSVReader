#include <iostream>
#include "CSVReader.h"
using namespace std;

int main() {
    CSVReader reader("test.csv");

    auto header = reader.getHeader();
    cout << "HEADER:" << endl;
    for(auto h : header) {
        cout << h << ' ';
    }
    cout << endl;

    int nRow = 0;
    cout << "RECORD:" << endl;
    while(reader.hasNext()) {
        auto fields = reader.getNextRecord();
        for(auto f : fields) {
            if(f.empty()) {
                cout << "<blank>";
            } else {
                for (auto ch : f) {
                    if (ch == '\n') {
                        cout << "<cr>";
                    } else {
                        cout << ch;
                    }
                }
            }
            cout << ' ';
        }
        cout << endl;
        ++nRow;
    }

    cout << "row number : " << nRow << endl;
    return 0;
}
