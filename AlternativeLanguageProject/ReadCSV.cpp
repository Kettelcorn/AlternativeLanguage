#include "ReadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>



ReadCSV::ReadCSV(const std::string& filename): filename(filename) {}

std::vector<std::string> ReadCSV::splitCSVLine(const std::string& line) {
	std::vector<std::string> result;
	std::stringstream ss(line);
	std::string value;
	bool insideQuote = false;
	char ch;
	std::string field;

	for (size_t i = 0; i < line.size(); ++i) {
		ch = line[i];
		if (ch == '"' && (i == 0 || line[i - 1] != '\\')) {
			insideQuote = !insideQuote;
			field += ch;
		}
		else if (ch == ',' && !insideQuote) {
			result.push_back(field);
			field.clear();
		}
		else {
			field += ch;
		}
	}
	result.push_back(field);
	return result;
}

std::string ReadCSV::parseLaunchStatus(const std::string& status) {
	if (status == "Discontinued" || status == "Cancelled" || status.find("Available. Released") != std::string::npos) {
		return status;
	}
	return "";
}

bool ReadCSV::containsDigits(const std::string& str) {
	return std::any_of(str.begin(), str.end(), ::isdigit);
}

bool ReadCSV::isValidInt(const std::string& str) {
	if (str.empty() || str == "-") return false;
	return containsDigits(str);
}

bool ReadCSV::isValidFloat(const std::string& str) {
	if (str.empty()) return false;
	std::istringstream iss(str);
	float f;
	return (iss >> f) && (iss.eof());
}

std::unordered_map<int, Cell> ReadCSV::read() {
	std::ifstream file(filename);
	std::unordered_map<int, Cell> data;
	std::string line;
	int index = 0;

	if (!file.is_open()) {
		std::cout << "Error: Could not open file: " << filename << std::endl;
		return data;
	}

	if (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string value;
		while (std::getline(ss, value, ',')) {
			columnNames = splitCSVLine(line);
		}
	}

	
	while (std::getline(file, line)) {
		std::vector<std::string> row = splitCSVLine(line);
	

		if (row.size() == 12) {
			try {
				Cell cell(
					(row[0].empty() || row[0] == "-") ? "" : row[0],
					(row[1].empty() || row[1] == "-") ? "": row[1],
					isValidInt(row[2]) ? std::stoi(row[2]) : 0,                                              
					parseLaunchStatus(row[3]),
					(row[4].empty() || row[4] == "-") ? "" : row[4],                                         
					isValidFloat(row[5]) ? std::stof(row[5]) : 0.0f,                                          
					(row[6] == "Yes" || row[6] == "No") ? "" : row[6],
					(row[7].empty() || row[7] == "-") ? "" : row[7],                                          
					isValidFloat(row[8]) ? std::stof(row[8]) : 0.0f,                                          
					(row[9].empty() || row[9] == "-") ? "" : row[9],                                          
					(row[10].empty() || row[10] == "-") ? "" : row[10],                                       
					(row[11].empty() || row[11] == "-") ? "" : row[11]
				);
				data[index++] = cell;
			} catch (const std::invalid_argument& e) {
				std::cout << "Warning: Invalid data in line: " << index + 1 << std::endl;
			} catch (const std::out_of_range& e) {
				std::cout << "Warning: Data out of range in line " << index + 1 << ": " << e.what() << std::endl;
			}
		}
		else {
			std::cout << "Warning: Incorrect number of columns in line: " << index + 1 << std::endl;
			index++;
		}
	}

	file.close();
	return data;
}

const std::vector<std::string>& ReadCSV::getColumnNames() const {
	return columnNames;
}






