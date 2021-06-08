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

	EffectGroup(const EffectGroup& effectGroup) 
		: label(effectGroup.label), feature(effectGroup.feature), effect(effect) {
	}

	EffectGroup(EffectGroup&& effectGroup) noexcept 
		: label(std::move(effectGroup.label)), feature(std::move(effectGroup.feature)), effect(std::move(effectGroup.effect)) {
	}

	EffectGroup() = default;
	~EffectGroup() = default;
};