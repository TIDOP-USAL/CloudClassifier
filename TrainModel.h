#pragma once

#include "TrainController.h"

class TrainModel {
private:
	TrainController trainController;
public:
	TrainModel(const TrainController& _trainController);
};