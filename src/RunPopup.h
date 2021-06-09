#pragma once

#include <QDialog>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>

#include "Classifier.h"

#define RUN_POPUP_TITLE "Run classification"

class RunPopup : public QDialog {
	Q_OBJECT
private:
	QGridLayout* layout;
	QDoubleSpinBox* spinGridResolution;
	QDoubleSpinBox* spinNumberOfNeighbors;
	QDoubleSpinBox* spinRadiusNeighbors;
	QDoubleSpinBox* spinRadiusDtm;
	QDoubleSpinBox* strengthSpinBox;

	QSpinBox* kNeighborsSpinBox;
	QSpinBox* subdivisionsSpinBox;

	QComboBox* comboClassification;

	QPushButton* buttonAccept;
	QPushButton* buttonCancel;
public:
	RunPopup(QWidget* parent = nullptr);
	RunPopup(QWidget* parent, float gridResolution, unsigned int numberOfNeighbors, float radiusNeighbors, float radiusDtm, unsigned int kNeighbors, double strength, unsigned int subdivisions);
	RunPopup(const RunPopup& runPopup);
	RunPopup(RunPopup&& runPopup) noexcept;
	~RunPopup() = default;
private:
	void enableGraphcut(bool enable);
	void addSeparator(int row, int col);
private slots:
	void ok();
	void cancel();
public:
	inline float getGridResolution() const {
		return spinGridResolution->value();
	}

	inline unsigned int getNumberOfNeighbors() const {
		return spinNumberOfNeighbors->value();
	}

	inline float getRadiusNeighbors() const {
		return spinRadiusNeighbors->value();
	}

	inline float getRadiusDtm() const {
		return spinRadiusDtm->value();
	}

	inline unsigned int getKNeighbors() const {
		return kNeighborsSpinBox->value();
	}

	inline double getStrength() const {
		return strengthSpinBox->value();
	}

	inline unsigned int getSubdivisions() const {
		return subdivisionsSpinBox->value();
	}

	inline QString& getClassificationType() {
		return comboClassification->itemText(comboClassification->currentIndex());
	}
};