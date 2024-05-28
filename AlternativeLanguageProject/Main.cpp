#include <iostream>
#include "ReadCSV.h"
#include "Cell.h"


int main() {
	const std::string filename = "cells.csv";
	ReadCSV reader(filename);
	std::unordered_map<int, Cell> data = reader.read();
	const std::vector<std::string>& columnNames = reader.getColumnNames();

    for (int i = 0; i < data.size(); ++i) {
		std::cout << "Cell " << i + 1 << ":" << std::endl;
		std::cout << data[i].toString() << std::endl;
    }

	return 0;
}