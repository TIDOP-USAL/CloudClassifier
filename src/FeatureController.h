#pragma once

#include <iostream>
#include <vector>

#include "FeatureView.h"

class FeatureController {
private:
	std::vector<FeatureView*> views;
public:
	FeatureController(const std::vector<FeatureView*>& _views);
	FeatureController(const FeatureController& featureController);
	FeatureController(FeatureController&& featureController) noexcept;
	FeatureController() = default;
	~FeatureController() = default;
public:
	FeatureController& operator=(const FeatureController& featureController);
public:
	inline std::vector<FeatureView*>& getViews() {
		return views;
	}
};