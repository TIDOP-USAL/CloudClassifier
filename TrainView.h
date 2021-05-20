#pragma once

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>

#include "Classifier.h"

class TrainView : public QDialog {
	Q_OBJECT
private:
	QGridLayout* layout;
	QSpinBox* scalesSpinBox;
	QComboBox* comboClassification;
	QPushButton* buttonAccept;
	QPushButton* buttonCancel;
public:
	TrainView(QWidget* parent = nullptr);
	TrainView(QWidget* parent, unsigned int scales);
	~TrainView() = default;
private slots:
	void ok();
	void cancel();
public:
	inline unsigned int getScales() const {
		return scalesSpinBox->value();
	}
	inline QString& getClassificationType() {
		return comboClassification->itemText(comboClassification->currentIndex());
	}

};