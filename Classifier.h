#pragma once

#include "FeatureManager.h"
#include "WeightGroup.h"
#include "EffectGroup.h"

typedef CGAL::Classification::Sum_of_weighted_features_classifier CGALclassifier;

#define CLASSIFICATION_RAW "Raw"
#define CLASSIFICATION_LOCAL_SMOOTHING "Local Smoothing"
#define CLASSIFICATION_GRAPHCUT "Graphcut"

enum class ClassificationType {
	NONE, RAW, LOCAL_SMOOTHING, GRAPHCUT
};

class Classifier {
private:
	FeatureManager featureManager;
	std::vector<int> labelIndices;
	std::vector<WeightGroup> weights;
	std::vector<EffectGroup> effects;
public:
	Classifier(FeatureManager& _featureManager);
	Classifier() = default;
	~Classifier() = default;
public:
	void classify(const ClassificationType& classificationType);
	void save(const std::string& filePath);
	void save();
public:
	inline void addWeight(WeightGroup& weightGroup) {
		weights.push_back(weightGroup);
	}

	inline void addEffect(EffectGroup& effectGroup) {
		effects.push_back(effectGroup);
	}
public:
	inline Input& getInput() {
		return featureManager.getAnalysis().getInput();
	}

	inline LabelManager& getLabelManager() {
		return featureManager.getAnalysis().getInput().getLabelManager();
	}

	inline Analysis& getAnalysis() {
		return featureManager.getAnalysis();
	}

	inline FeatureManager& getFeatureManager() {
		return featureManager;
	}
};