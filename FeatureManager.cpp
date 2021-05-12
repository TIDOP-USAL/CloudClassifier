#include "FeatureManager.h"

FeatureManager::FeatureManager(const Analysis& _analysis, float _radiusNeighbors, float _radiusDtm) 
	: analysis(_analysis), radiusNeighbors(_radiusNeighbors), radiusDtm(_radiusDtm) {
	featureSet.begin_parallel_additions();
	distanceToPlane = featureSet.add<DistanceToPlane>(analysis.getInput().getPoints(), Pmap(), analysis.getLocalEigenAnalysis());
	dispersion = featureSet.add<Dispersion>(analysis.getInput().getPoints(), Pmap(), analysis.getPlanimetricGrid(), radiusNeighbors);
	elevation = featureSet.add<Elevation>(analysis.getInput().getPoints(), Pmap(), analysis.getPlanimetricGrid(), radiusDtm);
	eigenValue0 = featureSet.add<Eigenvalue>(analysis.getInput().getPoints(), analysis.getLocalEigenAnalysis(), 0);
	eigenValue1 = featureSet.add<Eigenvalue>(analysis.getInput().getPoints(), analysis.getLocalEigenAnalysis(), 1);
	eigenValue2 = featureSet.add<Eigenvalue>(analysis.getInput().getPoints(), analysis.getLocalEigenAnalysis(), 2);
	heightAbove = featureSet.add<HeightAbove>(analysis.getInput().getPoints(), Pmap(), analysis.getPlanimetricGrid());
	heightBelow = featureSet.add<HeightBelow>(analysis.getInput().getPoints(), Pmap(), analysis.getPlanimetricGrid());
	verticalDispersion = featureSet.add<VerticalDispersion>(analysis.getInput().getPoints(), Pmap(), analysis.getPlanimetricGrid(), radiusNeighbors);
	verticalRange = featureSet.add<VerticalRange>(analysis.getInput().getPoints(), Pmap(), analysis.getPlanimetricGrid());
	verticality = featureSet.add<Verticality>(analysis.getInput().getPoints(), analysis.getLocalEigenAnalysis());
	featureSet.end_parallel_additions();
}

FeatureManager::FeatureManager(FeatureManager&& featureManager) noexcept 
	: featureSet(std::move(featureManager.featureSet)), analysis(featureManager.analysis), 
	radiusNeighbors(featureManager.radiusNeighbors), radiusDtm(featureManager.radiusDtm) {
	featureSet.begin_parallel_additions();
	distanceToPlane = featureManager.distanceToPlane;
	dispersion = featureManager.dispersion;
	elevation = featureManager.elevation;
	eigenValue0 = featureManager.eigenValue0;
	eigenValue1 = featureManager.eigenValue1;
	eigenValue2 = featureManager.eigenValue2;
	heightAbove = featureManager.heightAbove;
	heightBelow = featureManager.heightBelow;
	verticalDispersion = featureManager.verticalDispersion;
	verticalRange = featureManager.verticalRange;
	verticality = featureManager.verticality;
	featureSet.end_parallel_additions();
}

FeatureHandle& FeatureManager::getFeatureHandle(const std::string& featureName) {
	FeatureHandle featureHandle;
	if (featureName == std::string(DISTANCE_TO_PLANE))			return distanceToPlane;
	else if (featureName == std::string(DISPERSION))			return dispersion;
	else if (featureName == std::string(ELEVATION))				return elevation;
	else if (featureName == std::string(EIGEN_VALUE_0))			return eigenValue0;
	else if (featureName == std::string(EIGEN_VALUE_1))			return eigenValue1;
	else if (featureName == std::string(EIGEN_VALUE_2))			return eigenValue2;
	else if (featureName == std::string(HEIGHT_ABOVE))			return heightAbove;
	else if (featureName == std::string(HEIGHT_BELOW))			return heightBelow;
	else if (featureName == std::string(VERTICAL_DISPERSION))	return verticalDispersion;
	else if (featureName == std::string(VERTICAL_RANGE))		return verticalRange;
	else if (featureName == std::string(VERTICALITY))			return verticality;
	return featureHandle;
}

FeatureHandle* FeatureManager::getPtr(const FeatureHandle& featureHandle) {
	FeatureHandle* ptr = nullptr;
	if (featureHandle == distanceToPlane)						ptr = &distanceToPlane;
	else if (featureHandle == dispersion)						ptr = &dispersion;
	else if (featureHandle == elevation)						ptr = &elevation;
	else if (featureHandle == eigenValue0)						ptr = &eigenValue0;
	else if (featureHandle == eigenValue1)						ptr = &eigenValue1;
	else if (featureHandle == eigenValue2)						ptr = &eigenValue2;
	else if (featureHandle == heightAbove)						ptr = &heightAbove;
	else if (featureHandle == heightBelow)						ptr = &heightBelow;
	else if (featureHandle == verticalDispersion)				ptr = &verticalDispersion;
	else if (featureHandle == verticalRange)					ptr = &verticalRange;
	else if (featureHandle == verticality)						ptr = &verticality;
	return ptr;
}

FeatureHandle* FeatureManager::getPtr(const std::string& featureName) {
	FeatureHandle* ptr = nullptr;
	if (featureName == std::string(DISTANCE_TO_PLANE))			ptr = &distanceToPlane;
	else if (featureName == std::string(DISPERSION))			ptr = &dispersion;
	else if (featureName == std::string(ELEVATION))				ptr = &elevation;
	else if (featureName == std::string(EIGEN_VALUE_0))			ptr = &eigenValue0;
	else if (featureName == std::string(EIGEN_VALUE_1))			ptr = &eigenValue1;
	else if (featureName == std::string(EIGEN_VALUE_2))			ptr = &eigenValue2;
	else if (featureName == std::string(HEIGHT_ABOVE))			ptr = &heightAbove;
	else if (featureName == std::string(HEIGHT_BELOW))			ptr = &heightBelow;
	else if (featureName == std::string(VERTICAL_DISPERSION))	ptr = &verticalDispersion;
	else if (featureName == std::string(VERTICAL_RANGE))		ptr = &verticalRange;
	else if (featureName == std::string(VERTICALITY))			ptr = &verticality;
	return ptr;
}