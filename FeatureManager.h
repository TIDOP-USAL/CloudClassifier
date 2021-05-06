#pragma once

#include "Analysis.h"

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
	FeatureManager(const Analysis& _analysis, float _radiusNeighbors, float _radiusDtm);	// Rename when knowing what radiusDtm is...
	FeatureManager(const FeatureManager& featureManager) = delete;
	FeatureManager& operator=(const FeatureManager& featureManager) = delete;
	FeatureManager(FeatureManager&& featureManager) noexcept;
	FeatureManager() = default;
	~FeatureManager() = default;
	
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