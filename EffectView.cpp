#include "EffectView.h"

EffectView::EffectView(QWidget* parent, const char* name) {
	init(parent);
}

EffectView::EffectView(const std::vector<std::string>& _comboLabels, const std::vector<std::string>& _comboFeatures, QWidget* parent, const char* name)
	: comboLabels(_comboLabels), comboFeatures(_comboFeatures){
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

	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBoxLabels->itemText(comboBoxLabels->currentIndex()); });
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBoxLabels->itemText(comboBoxLabels->currentIndex()); });
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBoxLabels->itemText(comboBoxLabels->currentIndex()); });

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

	// Get indices
	indexLabel = comboBoxLabels->currentIndex();
	indexFeature = comboBoxFeatures->currentIndex();

	// Update combo
	for (std::string& text : comboLabels)
		comboBoxLabels->addItem(QString(text.c_str()));

	for (std::string& name : comboFeatures)
		comboBoxFeatures->addItem(QString(name.c_str()));

	// Set indices
	comboBoxLabels->setCurrentIndex(indexLabel);
	comboBoxFeatures->setCurrentIndex(indexFeature);
}