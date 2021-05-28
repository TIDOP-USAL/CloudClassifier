#pragma once

#include <QDialog>
#include <QSpinBox>
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
	QLineEdit* propertyEdit;
	QComboBox* comboClassification;
	QPushButton* buttonAccept;
	QPushButton* buttonCancel;
public:
	TrainView(QWidget* parent = nullptr);
	TrainView(QWidget* parent, unsigned int scales, unsigned int tests, const std::string& propertyName);
	TrainView(const TrainView& trainView);
	TrainView(TrainView&& trainView) noexcept;
	~TrainView() = default;
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

	inline QString& getPropertyName() {
		return propertyEdit->text();
	}

	inline QString& getClassificationType() {
		return comboClassification->itemText(comboClassification->currentIndex());
	}
};