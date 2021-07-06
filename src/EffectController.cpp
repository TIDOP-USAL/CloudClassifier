#include "EffectController.h"

EffectController::EffectController(const std::vector<EffectView*>& _views)
	: views(_views) {
}

EffectController::EffectController(const EffectController& effectController) 
	: views(effectController.views) {
}

EffectController::EffectController(EffectController&& effectController) noexcept 
	: views(std::move(effectController.views)) {
}

EffectController& EffectController::operator=(const EffectController& effectController) {
	views = effectController.views;
	return *this;
}