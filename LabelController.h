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
	LabelController() = default;
	~LabelController() = default;
public:
	inline std::vector<LabelView*>& getViews() {
		return views;
	}
};