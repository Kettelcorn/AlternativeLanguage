#include "ReadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>

// Constructor
ReadCSV::ReadCSV(const std::string& filename): filename(filename) {}

// Checks if a property has quotes around it to ignore commas inside the quotes.
// Splits the line by commas and returns a vector of strings.
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

// Parses the launch status to check if it is valid.
std::string ReadCSV::parseLaunchStatus(const std::string& status) {
	if (status == "Discontinued" || status == "Cancelled" || status.find("Available. Released") != std::string::npos) {
		return status;
	}
	return "";
}

// Checks if a string contains digits.
bool ReadCSV::containsDigits(const std::string& str) {
	return std::any_of(str.begin(), str.end(), ::isdigit);
}

// Checks if a string is a valid integer.
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

// Checks if a string is a valid float.
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

// Reads the CSV file and returns a map of cells.
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

// Returns the column names.
const std::vector<std::string>& ReadCSV::getColumnNames() const {
	return columnNames;
}

// Calculates the mean of a vector of floats.
float ReadCSV::calculateMean(const std::vector<float>& values) {
	if (values.empty()) return 0.0f;
	float sum = 0.0f;
	for (float value : values) {
		sum += value;
	}
	return sum / values.size();
}

// Returns a vector of unique values.
std::vector<std::string> ReadCSV::getUniqueValues(const std::vector<std::string>& values) {
	std::set<std::string> uniqueSet(values.begin(), values.end());
	return std::vector<std::string>(uniqueSet.begin(), uniqueSet.end());
}

// Returns a vector of cells with a specific launch status.
std::vector<Cell> ReadCSV::findByLaunchStatus(const std::string& status, const std::unordered_map<int, Cell>& data) const {
	std::vector<Cell> result;
	for (const auto& pair : data) {
		if (pair.second.getLaunchStatus() == status) {
			result.push_back(pair.second);
		}
	}
	return result;
}

// Returns the OEM with the highest average phone weight.
std::string ReadCSV::highestAveragePhoneWeight(std::unordered_map<int, Cell>& data) {
	std::unordered_map<std::string, std::vector<float>> weights;
	for (const auto& pair : data) {
		weights[pair.second.getOem()].push_back(pair.second.getBodyWeight());
	}
	std::string result;
	float maxWeight = 0.0f;
	for (const auto& pair : weights) {
		float mean = calculateMean(pair.second);
		if (mean > maxWeight) {
			maxWeight = mean;
			result = pair.first;
		}
	}
	return result;
}

// Returns a map of OEMs with models that have a different year in the launch status.
std::unordered_map<std::string, std::string> ReadCSV::findDifferentYear(std::unordered_map<int, Cell>& data) {
	std::unordered_map<std::string, std::string> result;
	for (const auto& pair : data) {
		std::string announcement = std::to_string(pair.second.getLaunchAnnounced());
		std::string status = pair.second.getLaunchStatus();
		if (status.find(announcement) == std::string::npos) {
			result[pair.second.getOem()] = pair.second.getModel();
		}
	}
	return result;
}

// Returns the number of phones with only one feature sensor.
int ReadCSV::onlyOneFeatureSensor(std::unordered_map<int, Cell>& data) {
	int count = 0;
	for (const auto& pair : data) {
		if (pair.second.getFeaturesSensors().find(",") == std::string::npos && !pair.second.getFeaturesSensors().empty()) {
			count++;
		}
	}
	return count;
}

// Returns the year with the most phones.
int ReadCSV::yearWithMostPhones(std::unordered_map<int, Cell>& data) {
	std::unordered_map<int, int> yearCount;
	for (const auto& pair : data) {
		if (pair.second.getLaunchAnnounced() > 1999) {
			yearCount[pair.second.getLaunchAnnounced()]++;
		}
	}
	int maxCount = 0;
	int year = 0;
	for (const auto& pair : yearCount) {
		if (pair.second > maxCount) {
			maxCount = pair.second;
			year = pair.first;
		}
	}
	return year;
}






