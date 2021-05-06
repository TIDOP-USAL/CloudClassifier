#pragma once

#include "FeatureManager.h"

struct WeightGroup {

	FeatureHandle feature;
	float weight;

	WeightGroup(const FeatureHandle& _feature, float _weight)
		: feature(_feature), weight(_weight) {
	}
	WeightGroup() = default;
	~WeightGroup() = default;
};