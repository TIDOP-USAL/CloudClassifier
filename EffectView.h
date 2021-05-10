#pragma once

#include <iostream>
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

#define EFFECT_VIEW_HEIGHT 50

class EffectView : public QWidget {
	Q_OBJECT
private:
	QLabel* qLabelLabels;
	QLabel* qLabelFeatures;
	QLabel* qLabelEffects;
	QComboBox* comboBoxLabels;
	QComboBox* comboBoxFeatures;
	QComboBox* comboBoxEffects;
	int indexLabels, indexFeatures;
	QString selectedLabelName, selectedFeatureName, selectedEffect;
	QHBoxLayout* layout;
private:
	std::vector<LabelView*> labelViews;
	std::vector<FeatureView*> featureViews;
public:
	EffectView(QWidget* parent, const char* name);
	EffectView(const std::vector<LabelView*>& _labelViews, const std::vector<FeatureView*>& _featureViews, QWidget* parent, const char* name);
	~EffectView();
private:
	void init(QWidget* parent);
public:
	void update();
public:
	inline std::string& getSelectedLabelName() {
		std::string label = selectedLabelName.toLocal8Bit().constData();
		return label;
	}

	inline std::string& getSelectedFeatureName() {
		std::string feature = selectedFeatureName.toLocal8Bit().constData();
		return feature;
	}

	inline std::string& getSelectedEffect() {
		std::string effect = selectedEffect.toLocal8Bit().constData();
		return effect;
	}
};