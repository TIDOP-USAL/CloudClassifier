#include "EffectView.h"

EffectView::EffectView(QWidget* parent, const char* name)
	: indexLabels(0), indexFeatures(0) {
	init(parent);
}

EffectView::EffectView(const std::vector<LabelView*>& _labelViews, const std::vector<FeatureView*>& _featureViews, QWidget* parent, const char* name)
	: labelViews(_labelViews), featureViews(_featureViews) {
	init(parent);
}

EffectView::~EffectView() {
	delete qLabelLabels;
	delete qLabelFeatures;
	delete qLabelEffects;
	delete comboBoxLabels;
	delete comboBoxFeatures;
	delete comboBoxEffects;
	delete layout;
}

void EffectView::init(QWidget* parent) {
	// Combo Boxes
	comboBoxLabels = new QComboBox(this);
	comboBoxFeatures = new QComboBox(this);
	update();

	comboBoxEffects = new QComboBox(this);
	comboBoxEffects->addItem(QString(EFFECT_NEUTRAL));
	comboBoxEffects->addItem(QString(EFFECT_PENALIZING));
	comboBoxEffects->addItem(QString(EFFECT_FAVORING));

	/*
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBox->itemText(comboBox->currentIndex()); });
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBox->itemText(comboBox->currentIndex()); });
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBox->itemText(comboBox->currentIndex()); });
	*/

	// QLabels
	qLabelLabels = new QLabel(this);
	qLabelLabels->setText("Label");

	qLabelFeatures = new QLabel(this);
	qLabelFeatures->setText("Features");

	qLabelEffects = new QLabel(this);
	qLabelEffects->setText("Effect");

	// Layout
	layout = new QHBoxLayout(this);
	layout->addWidget(qLabelLabels);
	layout->addWidget(comboBoxLabels);
	layout->addWidget(qLabelFeatures);
	layout->addWidget(comboBoxFeatures);
	layout->addWidget(qLabelEffects);
	layout->addWidget(comboBoxEffects);

	// Widget properties
	setFixedWidth(parent->width());
	setFixedHeight(EFFECT_VIEW_HEIGHT);
}

void EffectView::update() {

	// Save selected items
	indexLabels = comboBoxLabels->currentIndex();
	indexFeatures = comboBoxFeatures->currentIndex();

	// Update combo boxes
	comboBoxLabels->clear();
	comboBoxFeatures->clear();

	if (!labelViews.empty()) {
		for (LabelView* labelView : labelViews)
			comboBoxLabels->addItem(QString(labelView->getText().c_str()));
	}
	if (!featureViews.empty()) {
		for (FeatureView* featureView : featureViews)
			comboBoxFeatures->addItem(QString(featureView->getFeatureName().c_str()));
	}

	// Reselect previous item selected
	comboBoxLabels->setCurrentIndex(indexLabels);
	comboBoxFeatures->setCurrentIndex(indexFeatures);
}