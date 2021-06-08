#include "TrainController.h"

TrainController::TrainController(const std::string& _filePath,
	const std::vector<LabelView*>& _labelViews, const TrainView& _trainView) 
	: filePath(_filePath), labelViews(_labelViews), trainView(_trainView) {
}

TrainController::TrainController(const TrainController& trainController)
	: filePath(trainController.filePath), labelViews(trainController.labelViews), 
	trainView(trainController.trainView) {
}

TrainController::TrainController(TrainController&& trainController) noexcept 
	: filePath(std::move(trainController.filePath)), labelViews(std::move(trainController.labelViews)), 
	trainView(std::move(trainController.trainView)) {
}