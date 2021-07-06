#include "FeatureController.h"

FeatureController::FeatureController(const std::vector<FeatureView*>& _views)
	: views(_views) {
}

FeatureController::FeatureController(const FeatureController& featureController)
	: views(featureController.views) {
}

FeatureController::FeatureController(FeatureController&& featureController) noexcept
	: views(std::move(featureController.views)) {
}

FeatureController& FeatureController::operator=(const FeatureController& featureController) {
	views = featureController.views;
	return *this;
}