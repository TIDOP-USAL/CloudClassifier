#pragma once

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>

#include "Classifier.h"

#define TRAIN_VIEW_TITLE "Train"

class TrainView : public QDialog {
	Q_OBJECT
private:
	QGridLayout* layout;

	QSpinBox* scalesSpinBox;
	QSpinBox* testsSpinBox;
	QSpinBox* kNeighborsSpinBox;
	QSpinBox* subdivisionsSpinBox;

	QDoubleSpinBox* radiusNeighborsSpinBox;
	QDoubleSpinBox* strengthSpinBox;

	QLineEdit* propertyEdit;
	QComboBox* comboClassification;
	QPushButton* buttonAccept;
	QPushButton* buttonCancel;
public:
	TrainView(QWidget* parent = nullptr);
	TrainView(QWidget* parent, unsigned int scales, unsigned int tests, double radiusNeighbors, 
		unsigned int kNeighbors, double strength, unsigned int subdivisions, const std::string& propertyName);
	TrainView(const TrainView& trainView);
	TrainView(TrainView&& trainView) noexcept;
	~TrainView() = default;
private:
	void enableLocalSmoothing(bool enable);
	void enableGraphcut(bool enable);
	void addSeparator(int row, int col);
private slots:
	void ok();
	void cancel();
public:
	inline unsigned int getScales() const {
		return scalesSpinBox->value();
	}

	inline unsigned int getNumberOfTests() const {
		return testsSpinBox->value();
	}

	inline double getRadiusNeighbors() const {
		return radiusNeighborsSpinBox->value();
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

	inline QString& getPropertyName() {
		return propertyEdit->text();
	}

	inline QString& getClassificationType() {
		return comboClassification->itemText(comboClassification->currentIndex());
	}
};