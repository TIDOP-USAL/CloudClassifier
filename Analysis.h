#pragma once

#include "Input.h"

typedef Kernel::Iso_cuboid_3 BoundingBox;
typedef CGAL::Identity_property_map<Point> Pmap;
typedef CGAL::Classification::Planimetric_grid<Kernel, std::vector<Point>, Pmap> PlanimetricGrid;
typedef CGAL::Classification::Point_set_neighborhood<Kernel, std::vector<Point>, Pmap> Neighborhood;
typedef CGAL::Classification::Local_eigen_analysis LocalEigenAnalysis;

class Analysis {
private:
	Input input;

	BoundingBox boundingBox;
	PlanimetricGrid grid;
	Neighborhood neighborhood;
	LocalEigenAnalysis eigen;

	float gridResolution;
	unsigned int numberOfNeighbors;

public:
	Analysis(const Input& _input, float _gridResolution, unsigned int _numberOfNeighbors);
	Analysis(const Analysis& analysis);
	Analysis() = default;
	~Analysis() = default;

public:
	inline Input& getInput() {
		return input;
	}

	inline BoundingBox& getBoundingBox() {
		return boundingBox;
	}

	inline PlanimetricGrid& getPlanimetricGrid() {
		return grid;
	}

	inline Neighborhood& getNeighborhood() {
		return neighborhood;
	}

	inline LocalEigenAnalysis& getLocalEigenAnalysis() {
		return eigen;
	}

	inline float getGridResolution() {
		return gridResolution;
	}

	inline unsigned int getNumberOfNeighbors() {
		return numberOfNeighbors;
	}
};