#pragma once

#include <iostream>
#include <string>

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#define DISTANCE_TO_PLANE "Distance to plane"
#define DISPERSION "Dispersion"
#define ELEVATION "Elevation"
#define EIGEN_VALUE_0 "Eigen value 0"
#define EIGEN_VALUE_1 "Eigen value 1"
#define EIGEN_VALUE_2 "Eigen value 2"
#define HEIGHT_ABOVE "Height above"
#define HEIGHT_BELOW "Height below"
#define VERTICAL_DISPERSION "Vertical dispersion"
#define VERTICAL_RANGE "Vertical range"
#define VERTICALITY "Verticality"

#define FEATURE_VIEW_HEIGHT 50

class FeatureView : public QWidget {
	Q_OBJECT
private:
	QComboBox* comboBox;
	QLabel* label;
	QLineEdit* lineEdit;
	QHBoxLayout* layout;
	QString selectedFeatureName;
public:
	FeatureView(QWidget* parent, const char* name);
	~FeatureView();
public:
	inline std::string& getFeatureName() {
		std::string feature = selectedFeatureName.toLocal8Bit().constData();
		return feature;
	}

	inline float getWeight() const {
		std::string weightStr = lineEdit->text().toLocal8Bit().constData();
		return std::stof(weightStr);
	}
};