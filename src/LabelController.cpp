#include "LabelController.h"

LabelController::LabelController(const std::vector<LabelView*>& _views)
	: views(_views) {
}

LabelController::LabelController(const LabelController& labelController)
	: views(labelController.views) {
}

LabelController::LabelController(LabelController&& labelController) noexcept
	: views(std::move(labelController.views)){
}

LabelController& LabelController::operator=(const LabelController& labelController) {
	views = labelController.views;
	return *this;
}