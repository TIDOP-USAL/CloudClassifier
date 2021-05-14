#pragma once

#include <iostream>
#include <string>

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "FeatureManager.h"

#define FEATURE_VIEW_HEIGHT 50

class FeatureView : public QWidget {
	Q_OBJECT
private:
	unsigned int id;
	QComboBox* comboBox;
	QLabel* label;
	QLineEdit* lineEdit;
	QHBoxLayout* layout;
	QPushButton* deleteButton;
public:
	FeatureView(unsigned int _id, QWidget* parent, const char* name);
	~FeatureView();
signals:
	void deleteSignal(unsigned int);
public:
	inline unsigned int getID() const {
		return id;
	}

	inline QString& getFeatureName() {
		return comboBox->itemText(comboBox->currentIndex());
	}

	inline float getWeight() const {
		std::string weightStr = lineEdit->text().toLocal8Bit().constData();
		return std::stof(weightStr);
	}
};