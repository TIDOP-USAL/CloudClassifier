#pragma once

#include <iostream>
#include <vector>

#include "LabelView.h"
#include "TrainView.h"

class TrainController {
private:
	std::string filePath;
	std::vector<LabelView*> labelViews;
	TrainView trainView;
public:
	TrainController(const std::string& _filePath, const std::vector<LabelView*>& _labelViews, const TrainView& _trainView);
	TrainController(const TrainController& trainController);
	TrainController(TrainController&& trainController) noexcept;
	TrainController() = default;
	~TrainController() = default;
public:
	inline std::string getFilePath() {
		return filePath;
	}

	inline std::vector<LabelView*>& getLabelViews() {
		return labelViews;
	}

	inline QString& getClassificationType() {
		return trainView.getClassificationType();
	}

	inline unsigned int getScales() {
		return trainView.getScales();
	}

	inline unsigned int getNumberOfTests() {
		return trainView.getNumberOfTests();
	}
};