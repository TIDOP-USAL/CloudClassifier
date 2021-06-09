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
	EffectController(EffectController&& effectController) noexcept;
	EffectController() = default;
	~EffectController() = default;
public:
	EffectController& operator=(const EffectController& effectController);
public:
	inline std::vector<EffectView*>& getViews() {
		return views;
	}
};