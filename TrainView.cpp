#include "TrainView.h"

#include <QLabel>

TrainView::TrainView(QWidget* parent) 
	: QDialog(parent), scalesSpinBox(nullptr), testsSpinBox(nullptr), propertyEdit(nullptr), comboClassification(nullptr), 
	buttonAccept(nullptr), buttonCancel(nullptr), layout(nullptr) {
}

TrainView::TrainView(QWidget* parent, unsigned int scales, unsigned int tests, const std::string& propertyName) 
	: QDialog(parent), scalesSpinBox(nullptr), testsSpinBox(nullptr), propertyEdit(nullptr), comboClassification(nullptr),
	buttonAccept(nullptr), buttonCancel(nullptr), layout(nullptr) {

	QLabel* labelScales = new QLabel(this);
	labelScales->setText("Number of scales");

	QLabel* labelTests = new QLabel(this);
	labelTests->setText("Number of tests");

	QLabel* labelClassification = new QLabel(this);
	labelClassification->setText("Classification");

	QLabel* labelProperty = new QLabel();
	labelProperty->setText("Property (float)");

	scalesSpinBox = new QSpinBox(this);
	scalesSpinBox->setRange(0, 100);
	scalesSpinBox->setValue(scales);

	testsSpinBox = new QSpinBox(this);
	testsSpinBox->setRange(0, 1000);
	testsSpinBox->setValue(tests);

	propertyEdit = new QLineEdit(this);
	propertyEdit->setText(propertyName.c_str());

	comboClassification = new QComboBox(this);
	comboClassification->addItem(CLASSIFICATION_RAW);
	comboClassification->addItem(CLASSIFICATION_LOCAL_SMOOTHING);
	comboClassification->addItem(CLASSIFICATION_GRAPHCUT);

	buttonAccept = new QPushButton(this);
	buttonAccept->setText("Accept");

	buttonCancel = new QPushButton(this);
	buttonCancel->setText("Cancel");

	layout = new QGridLayout(this);
	layout->addWidget(labelScales, 0, 0);
	layout->addWidget(scalesSpinBox, 0, 1);
	layout->addWidget(labelTests, 1, 0);
	layout->addWidget(testsSpinBox, 1, 1);
	layout->addWidget(labelProperty, 2, 0);
	layout->addWidget(propertyEdit, 2, 1);
	layout->addWidget(labelClassification, 3, 0);
	layout->addWidget(comboClassification, 3, 1);
	layout->addWidget(buttonAccept, 4, 0);
	layout->addWidget(buttonCancel, 4, 1);

	setLayout(layout);
	
	connect(comboClassification, QOverload<int>::of(&QComboBox::activated), [=](int index)  { 
		comboClassification->itemText(comboClassification->currentIndex()); 
	});
	connect(buttonAccept, SIGNAL(clicked()), this, SLOT(ok()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

TrainView::TrainView(const TrainView& trainView)
	: scalesSpinBox(trainView.scalesSpinBox), testsSpinBox(trainView.testsSpinBox), propertyEdit(trainView.propertyEdit), 
	comboClassification(trainView.comboClassification),buttonAccept(trainView.buttonAccept), buttonCancel(trainView.buttonCancel), 
	layout(trainView.layout) {
}


TrainView::TrainView(TrainView&& trainView) noexcept
	: scalesSpinBox(std::move(trainView.scalesSpinBox)), testsSpinBox(std::move(trainView.testsSpinBox)),
	propertyEdit(std::move(trainView.propertyEdit)), comboClassification(std::move(trainView.comboClassification)),
	buttonAccept(std::move(trainView.buttonAccept)), buttonCancel(std::move(trainView.buttonCancel)), layout(std::move(trainView.layout)) {
}

void TrainView::ok() {
	accept();
	close();
}

void TrainView::cancel() {
	reject();
	close();
}