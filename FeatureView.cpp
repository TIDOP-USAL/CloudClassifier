#include "FeatureView.h"

FeatureView::FeatureView(QWidget* parent, const char* name) {

	comboBox = new QComboBox(this);
	comboBox->addItem(QString(DISTANCE_TO_PLANE));
	comboBox->addItem(QString(DISPERSION));
	comboBox->addItem(QString(ELEVATION));
	comboBox->addItem(QString(EIGEN_VALUE_0));
	comboBox->addItem(QString(EIGEN_VALUE_1));
	comboBox->addItem(QString(EIGEN_VALUE_2));
	comboBox->addItem(QString(HEIGHT_ABOVE));
	comboBox->addItem(QString(HEIGHT_BELOW));
	comboBox->addItem(QString(VERTICAL_DISPERSION));
	comboBox->addItem(QString(VERTICAL_RANGE));
	comboBox->addItem(QString(VERTICALITY));

	label = new QLabel(this);
	label->setText("Weight: ");

	lineEdit = new QLineEdit(this);
	lineEdit->setText("0.0");

	layout = new QHBoxLayout(this);
	layout->setMargin(10);
	layout->addWidget(comboBox);
	layout->addWidget(label);
	layout->addWidget(lineEdit);

	setFixedWidth(parent->width() - 25);
	setFixedHeight(FEATURE_VIEW_HEIGHT);

	connect(comboBox, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboBox->itemText(comboBox->currentIndex()); });
}

FeatureView::~FeatureView() {
	delete comboBox;
	delete label;
	delete lineEdit;
	delete layout;
}