#include "EffectView.h"

EffectView::EffectView(QWidget* parent, const char* name) {
	init(parent);
}

EffectView::EffectView(const std::vector<std::string>& _comboLabels, const std::vector<std::string>& _comboFeatures, QWidget* parent, const char* name)
	: comboLabels(_comboLabels), comboFeatures(_comboFeatures){
	init(parent);
}

void EffectView::init(QWidget* parent) {

	this->parent = parent;

	// Combo Boxes
	comboBoxLabels = new QComboBox(this);
	comboBoxLabels->setEnabled(false);
	comboBoxFeatures = new QComboBox(this);
	comboBoxFeatures->setEnabled(false);
	update();

	comboBoxEffects = new QComboBox(this);
	comboBoxEffects->addItem(QString(EFFECT_NEUTRAL));
	comboBoxEffects->addItem(QString(EFFECT_PENALIZING));
	comboBoxEffects->addItem(QString(EFFECT_FAVORING));

	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBoxLabels->itemText(comboBoxLabels->currentIndex()); });
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBoxLabels->itemText(comboBoxLabels->currentIndex()); });
	connect(comboBoxLabels, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBoxLabels->itemText(comboBoxLabels->currentIndex()); });

	const QString lineStyleSheet = "background-color: rgb(150, 150, 255);";
	QFrame* line = new QFrame(this);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	line->setStyleSheet(lineStyleSheet);

	QFrame* line2 = new QFrame(this);
	line2->setFrameShape(QFrame::HLine);
	line2->setFrameShadow(QFrame::Sunken);
	line2->setStyleSheet(lineStyleSheet);

	// Layout
	layout = new QHBoxLayout(this);
	layout->addWidget(comboBoxLabels);
	layout->addWidget(line);
	layout->addWidget(comboBoxFeatures);
	layout->addWidget(line2);
	layout->addWidget(comboBoxEffects);

	// Widget properties
	updateSize();
}

void EffectView::updateSize() {
	setFixedWidth(parent->width() - 50);
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