#pragma once

#include <iostream>
#include <string>

#define FORMAT_ASCII "format ascii"
#define FORMAT_BINARY "format binary"

class BinaryCheck {
public:
	static bool find(const std::string& str, const std::string& s);
	static bool check(const std::string& filePath);
};