#pragma once

#include "Analysis.h"

#define DISTANCE_TO_PLANE "Distance to plane"
#define DISPERSION "Dispersion"
#define ELEVATION "Elevation"
#define EIGEN_VALUE_0 "Eigen value 0"
#define EIGEN_VALUE_1 "Eigen value 1"
#define EIGEN_VALUE_2 "Eigen value 2"
#define HEIGHT_ABOVE "Height above"
#define HEIGHT_BELOW "Height below"
#define VERTICAL_DISPERSION "Vertical dispersion"
#define VERTICAL_RANGE "Vertical range"
#define VERTICALITY "Verticality"

typedef CGAL::Classification::Feature_handle FeatureHandle;
typedef CGAL::Classification::Feature_set FeatureSet;
typedef CGAL::Classification::Feature::Distance_to_plane<std::vector<Point>, Pmap> DistanceToPlane;
typedef CGAL::Classification::Feature::Elevation<Kernel, std::vector<Point>, Pmap> Elevation;
typedef CGAL::Classification::Feature::Vertical_dispersion<Kernel, std::vector<Point>, Pmap> Dispersion;
typedef CGAL::Classification::Feature::Eigenvalue Eigenvalue;
typedef CGAL::Classification::Feature::Height_above<Kernel, std::vector<Point>, Pmap> HeightAbove;
typedef CGAL::Classification::Feature::Height_below<Kernel, std::vector<Point>, Pmap> HeightBelow;
typedef CGAL::Classification::Feature::Vertical_dispersion<Kernel, std::vector<Point>, Pmap> VerticalDispersion;
typedef CGAL::Classification::Feature::Vertical_range<Kernel, std::vector<Point>, Pmap> VerticalRange;
typedef CGAL::Classification::Feature::Verticality<Kernel> Verticality;

class FeatureManager {
private:
	FeatureSet featureSet;
	FeatureHandle distanceToPlane, dispersion, elevation, eigenValue0, eigenValue1, eigenValue2, 
		heightAbove, heightBelow, verticalDispersion, verticalRange, verticality;
	float radiusNeighbors, radiusDtm;
	Analysis analysis;
public:
	FeatureManager(const Analysis& _analysis, float _radiusNeighbors, float _radiusDtm);
	FeatureManager(const FeatureManager& featureManager) = delete;
	FeatureManager(FeatureManager&& featureManager) noexcept;
	FeatureManager() = default;
	~FeatureManager() = default;
	FeatureManager& operator=(const FeatureManager& featureManager) = delete;
public:
	FeatureHandle& getFeatureHandle(const std::string& featureName);
	FeatureHandle* getPtr(const FeatureHandle& featureHandle);
	FeatureHandle* getPtr(const std::string& featureName);
public:
	inline FeatureSet& getFeatureSet() {
		return featureSet;
	}

	inline FeatureHandle& getDistanceToPlane() {
		return distanceToPlane;
	}

	inline FeatureHandle& getDispersion() {
		return dispersion;
	}

	inline FeatureHandle& getElevation() {
		return elevation;
	}

	inline FeatureHandle& getEigenValue0() {
		return eigenValue0;
	}

	inline FeatureHandle& getEigenValue1() {
		return eigenValue1;
	}

	inline FeatureHandle& getEigenValue2() {
		return eigenValue2;
	}

	inline FeatureHandle& getHeightAbove() {
		return heightAbove;
	}

	inline FeatureHandle& getHeightBelow() {
		return heightBelow;
	}

	inline FeatureHandle& getVerticalDispersion() {
		return verticalDispersion;
	}

	inline FeatureHandle& getVerticalRange() {
		return verticalRange;
	}

	inline FeatureHandle& getVerticality() {
		return verticality;
	}

	inline Analysis& getAnalysis() {
		return analysis;
	}

	float getRadiusNeighbors() const {
		return radiusNeighbors;
	}

	float getRadiusDtm() const {
		return radiusDtm;
	}
};