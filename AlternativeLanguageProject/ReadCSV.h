#ifndef READCSV_H
#define READCSV_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Cell.h"

class ReadCSV {
public:
    ReadCSV(const std::string& filename);
	std::vector<std::string> splitCSVLine(const std::string& line);
	std::string parseLaunchStatus(const std::string& status);
	bool containsDigits(const std::string& str);
	bool isValidInt(const std::string& str);
	bool isValidFloat(const std::string& str);
    std::unordered_map<int, Cell> read();
    const std::vector<std::string>& getColumnNames() const;


private:
    const std::string& filename;
	std::vector<std::string> columnNames;
};

#endif // READCSV_H


