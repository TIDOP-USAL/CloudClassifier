#pragma once

#include "Input.h"

#include <fstream>

#include <CGAL/IO/read_ply_points.h>

Input::Input(const std::string& _filePath) : filePath(_filePath) {
	readPointCloud();
	labelManager = LabelManager();
}

Input::Input(const Input& input) 
	: points(input.points), labelManager(input.labelManager), filePath(input.filePath) {
}

void Input::readPointCloud() {
	std::ifstream in(filePath);
	if (!in || !(CGAL::read_ply_points(in, std::back_inserter(points))))
		std::cerr << "Error: cannot read " << filePath << std::endl;
}