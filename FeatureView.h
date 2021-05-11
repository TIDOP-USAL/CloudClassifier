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
	QComboBox* comboBox;
	QLabel* label;
	QLineEdit* lineEdit;
	QHBoxLayout* layout;
public:
	FeatureView(QWidget* parent, const char* name);
	~FeatureView();
public:
	inline QString& getFeatureName() {
		return comboBox->itemText(comboBox->currentIndex());
	}

	inline float getWeight() const {
		std::string weightStr = lineEdit->text().toLocal8Bit().constData();
		return std::stof(weightStr);
	}
};