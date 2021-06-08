#include "BinaryCheck.h"

#include <fstream>

bool BinaryCheck::find(const std::string& str, const std::string& s) {
	return (str.find(s) != std::string::npos) ? true : false;
}

bool BinaryCheck::check(const std::string& filePath) {
	std::ifstream file(filePath);
	if (file.is_open()) {
		std::string line = "";
		while (getline(file, line)) {
			if (find(line, std::string(FORMAT_ASCII)))
				return false;
			else if (find(line, std::string(FORMAT_BINARY)))
				return true;
		}
		file.close();
	}
	return true;
}