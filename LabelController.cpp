#include "LabelController.h"

LabelController::LabelController(const std::vector<LabelView*>& _views)
	: views(_views) {
}

LabelController::LabelController(const LabelController& labelController)
	: views(labelController.views) {
}
