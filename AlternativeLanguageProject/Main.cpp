#include <iostream>
#include "ReadCSV.h"
#include "Cell.h"


int main() {
	const std::string filename = "cells.csv";
	ReadCSV reader(filename);
	std::unordered_map<int, Cell> data = reader.read();
	const std::vector<std::string>& columnNames = reader.getColumnNames();

    for (int i = 0; i < data.size(); ++i) {
        const Cell& cell = data[i];
        std::cout << "Index: " << i << " -> "
            << cell.getOem() << " "
            << cell.getModel() << " "
            << cell.getLaunchAnnounced() << " "
            << cell.getLaunchStatus() << " "
            << cell.getBodyDimensions() << " "
            << cell.getBodyWeight() << " "
            << cell.getDisplayType() << " "
            << cell.getDisplaySize() << " "
            << cell.getDisplayResolution() << " "
            << cell.getFeaturesSensors() << " "
            << cell.getPlatformOs() << std::endl;
		std::cout << std::endl;
    }

	return 0;
}