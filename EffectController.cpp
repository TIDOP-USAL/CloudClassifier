#include "EffectController.h"

EffectController::EffectController(const std::vector<EffectView*>& _views)
	: views(_views) {
}

EffectController::EffectController(const EffectController& effectController) 
	: views(effectController.views) {
}