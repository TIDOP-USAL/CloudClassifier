#pragma once

#include <iostream>
#include <vector>

#include "LabelView.h"
#include "TrainView.h"

class TrainController {
private:
	std::vector<LabelView*> labelViews;
	TrainView trainView;	// Get info from here and send it to the model
public:
	TrainController(const std::vector<LabelView*>& _labelViews, const TrainView& _trainView);
	TrainController() = default;
	~TrainController() = default;
public:

};