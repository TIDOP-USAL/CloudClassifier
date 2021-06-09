#pragma once

#include "LabelController.h"
#include "FeatureController.h"
#include "EffectController.h"
#include "RunPopup.h"

struct ControllerGroup {

	LabelController labelController;
	FeatureController featureController;
	EffectController effectController;
	RunPopup* runPopup;

	ControllerGroup() = default;
	
	ControllerGroup(LabelController& _labelController, FeatureController& _featureController, 
		EffectController& _effectController, RunPopup* _runPopup)
		: labelController(_labelController), featureController(_featureController), 
		effectController(_effectController), runPopup(_runPopup) {
	}

	ControllerGroup(const ControllerGroup& controllerGroup)
		: labelController(controllerGroup.labelController), featureController(controllerGroup.featureController), 
		effectController(controllerGroup.effectController), runPopup(controllerGroup.runPopup) {
	}

	ControllerGroup(ControllerGroup&& controllerGroup) noexcept
		: labelController(std::move(controllerGroup.labelController)), featureController(std::move(controllerGroup.featureController)),
		effectController(std::move(controllerGroup.effectController)), runPopup(std::move(controllerGroup.runPopup)) {
	}

	~ControllerGroup() = default;

	inline float getGridResolution() const {
		return runPopup->getGridResolution();
	}

	inline unsigned int getNumberOfNeighbors() const {
		return runPopup->getNumberOfNeighbors();
	}

	inline float getRadiusNeighbors() const {
		return runPopup->getRadiusNeighbors();
	}

	inline float getRadiusDtm() const {
		return runPopup->getRadiusDtm();
	}

	inline unsigned int getKNeighbors() const {
		return runPopup->getKNeighbors();
	}

	inline double getStrength() const {
		return runPopup->getStrength();
	}

	inline unsigned int getSubdivisions() const {
		return runPopup->getSubdivisions();
	}

	inline QString& getClassificationType() {
		return runPopup->getClassificationType();
	}
};