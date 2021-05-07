#pragma once

#include "Input.h"

#include <fstream>

#include <CGAL/IO/read_ply_points.h>

#include <QProgressDialog>

Input::Input(const std::string& _filePath) : filePath(_filePath) {
	readPointCloud();
	labelManager = LabelManager();
}

Input::Input(const Input& input) 
	: points(input.points), labelManager(input.labelManager), filePath(input.filePath) {
}

void Input::readPointCloud() {

	QProgressDialog progressDialog("Loading Point Cloud [CGAL]", "Cancel", 0, 1);
	progressDialog.setValue(0);
	progressDialog.setWindowModality(Qt::WindowModal);

	std::ifstream in(filePath);
	if (!in || !(CGAL::read_ply_points(in, std::back_inserter(points))))
		std::cerr << "Error: cannot read " << filePath << std::endl;

	progressDialog.setValue(1);
}