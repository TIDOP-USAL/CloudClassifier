#pragma once

#include <iostream>
#include <string>
#include <map>

#include "LabelController.h"
#include "FeatureController.h"
#include "EffectController.h"

#include "Input.h"
#include "Analysis.h"
#include "FeatureManager.h"
#include "Classifier.h"

class ClassificationModel {
private:
	LabelController labelController;
	FeatureController featureController;
	EffectController effectController;

	std::string filePath;
	Input* input;
	Analysis* analysis;
	FeatureManager* featureManager;
	Classifier* classifier;
public:
	ClassificationModel(const std::string& _filePath, const LabelController& _labelController, 
		const FeatureController& _featureController, const EffectController& _effectController);
	ClassificationModel() = default;
	~ClassificationModel();
public:
	void run();
public:
	inline Input* getInput() {
		return input;
	}

	inline Analysis* getAnalysis() {
		return analysis;
	}

	inline FeatureManager* getFeatureManager() {
		return featureManager;
	}

	inline Classifier* getClassifier() {
		return classifier;
	}

	inline LabelController& getLabelController() {
		return labelController;
	}

	inline FeatureController& getFeatureController() {
		return featureController;
	}

	inline EffectController& getEffectController() {
		return effectController;
	}
};