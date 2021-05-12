#pragma once

#include "FeatureManager.h"

struct WeightGroup {

	FeatureHandle feature;
	float weight;

	WeightGroup(const FeatureHandle& _feature, float _weight)
		: feature(_feature), weight(_weight) {
	}

	WeightGroup(const WeightGroup& weightGroup)
		: feature(weightGroup.feature), weight(weightGroup.weight) {
	}

	WeightGroup(WeightGroup&& weightGroup) noexcept
		: feature(std::move(weightGroup.feature)), weight(weightGroup.weight) {
	}

	WeightGroup() = default;
	~WeightGroup() = default;
};