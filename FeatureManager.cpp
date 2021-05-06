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
