#include "TrainView.h"

#include <QLabel>

TrainView::TrainView(QWidget* parent) 
	: QDialog(parent), scalesSpinBox(nullptr), testsSpinBox(nullptr), comboClassification(nullptr), 
	buttonAccept(nullptr), buttonCancel(nullptr), layout(nullptr) {
}

TrainView::TrainView(QWidget* parent, unsigned int scales, unsigned int tests) 
	: QDialog(parent), scalesSpinBox(nullptr), testsSpinBox(nullptr), comboClassification(nullptr),
	buttonAccept(nullptr), buttonCancel(nullptr), layout(nullptr) {

	QLabel* labelScales = new QLabel(this);
	labelScales->setText("Number of scales");

	QLabel* labelTests = new QLabel(this);
	labelTests->setText("Number of tests");

	QLabel* labelClassification = new QLabel(this);
	labelClassification->setText("Classification");

	scalesSpinBox = new QSpinBox(this);
	scalesSpinBox->setRange(0, 100);
	scalesSpinBox->setValue(scales);

	testsSpinBox = new QSpinBox(this);
	testsSpinBox->setRange(0, 1000);
	testsSpinBox->setValue(tests);

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
	layout->addWidget(labelClassification, 2, 0);
	layout->addWidget(comboClassification, 2, 1);
	layout->addWidget(buttonAccept, 3, 0);
	layout->addWidget(buttonCancel, 3, 1);

	setLayout(layout);
	
	connect(comboClassification, QOverload<int>::of(&QComboBox::activated), [=](int index)  { 
		comboClassification->itemText(comboClassification->currentIndex()); 
	});
	connect(buttonAccept, SIGNAL(clicked()), this, SLOT(ok()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

TrainView::TrainView(const TrainView& trainView)
	: scalesSpinBox(trainView.scalesSpinBox), testsSpinBox(trainView.testsSpinBox), comboClassification(trainView.comboClassification),
	buttonAccept(trainView.buttonAccept), buttonCancel(trainView.buttonCancel), layout(trainView.layout) {
}


TrainView::TrainView(TrainView&& trainView) noexcept
	: scalesSpinBox(std::move(trainView.scalesSpinBox)), testsSpinBox(std::move(trainView.testsSpinBox)), comboClassification(std::move(trainView.comboClassification)),
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