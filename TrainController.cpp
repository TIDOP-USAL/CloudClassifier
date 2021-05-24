#include "TrainController.h"

TrainController::TrainController(const std::vector<LabelView*>& _labelViews, const TrainView& _trainView) 
	: labelViews(_labelViews), trainView(_trainView) {
}

TrainController::TrainController(const TrainController& trainController)
	: labelViews(trainController.labelViews), trainView(trainController.trainView) {
}

TrainController::TrainController(TrainController&& trainController) noexcept 
	: labelViews(std::move(trainController.labelViews)), trainView(std::move(trainController.trainView)) {
}