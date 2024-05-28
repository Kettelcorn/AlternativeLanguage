#include "ReadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>



ReadCSV::ReadCSV(const std::string& filename): filename(filename) {}

std::vector<std::string> ReadCSV::splitCSVLine(const std::string& line) {
	std::vector<std::string> result;
	std::string field;
	bool insideQuote = false;

	for (char ch : line) {
		if (ch == '"' && (field.empty() || field.back() != '\\')) {
			insideQuote = !insideQuote;
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
	if (str.empty() || str == "-" || !containsDigits(str)) return false;
	try {
		std::stoi(str);
		return true;
	}
	catch (const std::invalid_argument& e) {
		return false;
	}
	catch (const std::out_of_range& e) {
		return false;
	}
}

bool ReadCSV::isValidFloat(const std::string& str) {
	if (str.empty() || str == "-") return false;
	try {
		std::stof(str);
		return true;
	}
	catch (const std::invalid_argument& e) {
		return false;
	}
	catch (const std::out_of_range& e) {
		return false;
	}
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
		std::vector<std::string> columns = splitCSVLine(line);
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
					(row[6] == "Yes" || row[6] == "No" || containsDigits(row[6])) ? "" : row[6],
					(row[7].empty() || row[7] == "-") ? "" : row[7],                                          
					isValidFloat(row[8]) ? std::stof(row[8]) : 0.0f,                                          
					(row[9].empty() || row[9] == "-") ? "" : row[9],                                          
					(row[10].empty() || row[10] == "-" || isValidInt(row[10]) || isValidFloat(row[10])) ? "" : row[10],
					(row[11].empty() || row[11] == "-" || isValidInt(row[11]) || isValidFloat(row[11])) ? "" : row[11]
				);
				data[index++] = cell;
			}
			catch (const std::invalid_argument& e) {
				std::cout << "Warning: Invalid data in line " << index + 1 << ": " << e.what() << " for value: " << row[2] << ", " << row[5] << ", " << row[8] << std::endl;
			}
			catch (const std::out_of_range& e) {
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

float ReadCSV::calculateMean(const std::vector<float>& values) {
	if (values.empty()) return 0.0f;
	float sum = 0.0f;
	for (float value : values) {
		sum += value;
	}
	return sum / values.size();
}

std::vector<std::string> ReadCSV::getUniqueValues(const std::vector<std::string>& values) {
	std::set<std::string> uniqueSet(values.begin(), values.end());
	return std::vector<std::string>(uniqueSet.begin(), uniqueSet.end());
}

std::vector<Cell> ReadCSV::findByLaunchStatus(const std::string& status, const std::unordered_map<int, Cell>& data) const {
	std::vector<Cell> result;
	for (const auto& pair : data) {
		if (pair.second.getLaunchStatus() == status) {
			result.push_back(pair.second);
		}
	}
	return result;
}






