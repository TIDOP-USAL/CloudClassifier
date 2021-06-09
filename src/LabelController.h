#pragma once

#include <iostream>
#include <vector>

#include "LabelView.h"

class LabelController {
private:
	std::vector<LabelView*> views;
public:
	LabelController(const std::vector<LabelView*>& _views);
	LabelController(const LabelController& labelController);
	LabelController(LabelController&& labelController) noexcept;
	LabelController() = default;
	~LabelController() = default;
public:
	LabelController& operator=(const LabelController& labelController);
public:
	inline std::vector<LabelView*>& getViews() {
		return views;
	}
};