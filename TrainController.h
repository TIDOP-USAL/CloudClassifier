#pragma once

#include <iostream>
#include <vector>

#include "LabelView.h"
#include "TrainView.h"

class TrainController {
private:
	std::vector<LabelView*> labelViews;
	TrainView trainView;
public:
	TrainController(const std::vector<LabelView*>& _labelViews, const TrainView& _trainView);
	TrainController(const TrainController& trainController);
	TrainController(TrainController&& trainController) noexcept;
	TrainController() = default;
	~TrainController() = default;
public:
	inline unsigned int getScales() {
		return trainView.getScales();
	}

	inline unsigned int getNumberOfTests() {
		return trainView.getNumberOfTests();
	}
};