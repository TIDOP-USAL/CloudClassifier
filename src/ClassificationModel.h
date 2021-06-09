#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Input.h"
#include "Analysis.h"
#include "FeatureManager.h"
#include "Classifier.h"

#include "ControllerGroup.h"

#include <QProgressDialog>

class ClassificationModel {
private:
	ControllerGroup controllerGroup;
	std::string filePath;
	Input* input;
	Analysis* analysis;
	FeatureManager* featureManager;
	std::map<FeatureHandle, float> weightMap;
	Classifier* classifier;
public:
	ClassificationModel(const std::string& _filePath, const ControllerGroup& controllerGroup);
	ClassificationModel() = default;
	~ClassificationModel();
private:
	void initInput(const std::string& filePath);
	inline void initAnalysis(float gridResolution, unsigned int numberOfNeighbors);
	void initFeatureManager(float radiusNeighbors, float radiusDtm);
	inline void initClassifier();
	void applyWeights();
	void applyEffects();
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

	inline ControllerGroup& getControllerGroup() {
		return controllerGroup;
	}

	inline LabelController& getLabelController() {
		return controllerGroup.labelController;
	}

	inline FeatureController& getFeatureController() {
		return controllerGroup.featureController;
	}

	inline EffectController& getEffectController() {
		return controllerGroup.effectController;
	}
};