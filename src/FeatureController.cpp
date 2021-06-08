#include "FeatureController.h"

FeatureController::FeatureController(const std::vector<FeatureView*>& _views)
	: views(_views) {
}

FeatureController::FeatureController(const FeatureController& featureController)
	: views(featureController.views) {
}