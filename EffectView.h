#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "LabelView.h"
#include "FeatureView.h"

#define EFFECT_NEUTRAL "Neutral"
#define EFFECT_PENALIZING "Penalizing"
#define EFFECT_FAVORING "Favoring"

#define EFFECT_VIEW_WIDTH 850
#define EFFECT_VIEW_HEIGHT 50

class EffectView : public QWidget {
	Q_OBJECT
private:
	QWidget* parent;
	QComboBox* comboBoxLabels;
	QComboBox* comboBoxFeatures;
	QComboBox* comboBoxEffects;

	int indexLabel, indexFeature;
	QString selectedLabelName, selectedFeatureName, selectedEffect;

	QHBoxLayout* layout;
private:
	std::vector<std::string> comboLabels;
	std::vector<std::string> comboFeatures;
public:
	EffectView(QWidget* parent, const char* name);
	EffectView(const std::vector<std::string>& _comboLabels, const std::vector<std::string>& _comboFeatures, QWidget* parent, const char* name);
	~EffectView() = default;
private:
	void init(QWidget* parent);
public:
	void updateSize();
	void update();
public:

	inline QString& getSelectedLabelName() {
		return comboBoxLabels->itemText(comboBoxLabels->currentIndex());
	}

	inline QString& getSelectedFeatureName() {
		return comboBoxFeatures->itemText(comboBoxFeatures->currentIndex());
	}

	inline QString& getSelectedEffect() {
		return comboBoxEffects->itemText(comboBoxEffects->currentIndex());
	}

	inline QComboBox* getComboBoxLabels() {
		return comboBoxLabels;
	}

	inline QComboBox* getComboBoxFeatures() {
		return comboBoxFeatures;
	}

	inline QComboBox* getComboBoxEffects() {
		return comboBoxEffects;
	}
};