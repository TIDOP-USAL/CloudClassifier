#pragma once

#include "Classifier.h"

typedef CGAL::Classification::Sum_of_weighted_features_classifier::Effect Effect;

struct  EffectGroup {

	LabelHandle label;
	FeatureHandle feature;
	Effect effect;

	EffectGroup(const LabelHandle& _label, const FeatureHandle& _feature, const Effect& _effect)
		: label(_label), feature(_feature), effect(_effect) {
	}
	EffectGroup() = default;
	~EffectGroup() = default;
};