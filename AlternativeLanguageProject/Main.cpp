#include <iostream>
#include "ReadCSV.h"
#include "Cell.h"


int main() {
	const std::string filename = "cells.csv";
	ReadCSV reader(filename);
	std::unordered_map<int, Cell> data = reader.read();
	const std::vector<std::string>& columnNames = reader.getColumnNames();
	
	std::string highestAveragePhoneWeight = reader.highestAveragePhoneWeight(data);
	std::cout << "Highest Average Phone Weight: " << reader.highestAveragePhoneWeight(data) << std::endl;
	std::cout << std::endl;

	std::unordered_map<std::string, std::string> differentYear = reader.findDifferentYear(data);
	std::cout << "Different Year: " << std::endl;	
	for (const auto& pair : differentYear) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Number of phones with only one feature: " <<reader.onlyOneFeatureSensor(data) << std::endl;
	std::cout << std::endl;
	std::cout << "Year with most phones: " << reader.yearWithMostPhones(data) << std::endl;
	std::cout << std::endl;

	return 0;
}