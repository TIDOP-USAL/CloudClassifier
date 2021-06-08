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

	inline unsigned int getScales() const {
		return trainView.getScales();
	}

	inline unsigned int getNumberOfTests() const {
		return trainView.getNumberOfTests();
	}

	inline double getRadiusNeighbors() const {
		return trainView.getRadiusNeighbors();
	}

	inline unsigned int getKNeighbors() const {
		return trainView.getKNeighbors();
	}

	inline double getStrength() const {
		return trainView.getStrength();
	}

	inline unsigned int getSubdivisions() const {
		return trainView.getSubdivisions();
	}

	inline QString& getPropertyName() {
		return trainView.getPropertyName();
	}
};