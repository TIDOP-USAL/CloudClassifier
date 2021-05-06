#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>

#include "LabelManager.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef CGAL::Classification::Label_set Label_set;
typedef CGAL::Classification::Label_handle Label_handle;

class Input {
private:
	std::string filePath;
	std::vector<Point> points;
	LabelManager labelManager;

public:
	Input(const std::string& _filePath);
	Input(const Input& input);
	Input() = default;
	~Input() = default;

private:
	void readPointCloud();

public:
	inline std::vector<Point>& getPoints() {
		return points;
	}

	inline LabelManager& getLabelManager() {
		return labelManager;
	}

	inline std::string& getFilePath() {
		return filePath;
	}
};