#pragma once

#include <iostream>
#include <vector>

#include "EffectView.h"

class EffectController {
private:
	std::vector<EffectView*> views;
public:
	EffectController(const std::vector<EffectView*>& _views);
	EffectController(const EffectController& effectController);
	EffectController() = default;
	~EffectController() = default;
public:
	inline std::vector<EffectView*>& getViews() {
		return views;
	}
};