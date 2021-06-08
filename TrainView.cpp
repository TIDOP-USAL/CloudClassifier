#include "TrainView.h"

#include <QLabel>

TrainView::TrainView(QWidget* parent) 
	: QDialog(parent), scalesSpinBox(nullptr), testsSpinBox(nullptr), propertyEdit(nullptr), comboClassification(nullptr), 
	buttonAccept(nullptr), buttonCancel(nullptr), radiusNeighborsSpinBox(nullptr), kNeighborsSpinBox(nullptr), 
	subdivisionsSpinBox(nullptr), strengthSpinBox(nullptr), layout(nullptr) {
}

TrainView::TrainView(QWidget* parent, unsigned int scales, unsigned int tests, double radiusNeighbors,
	unsigned int kNeighbors, double strength, unsigned int subdivisions, const std::string& propertyName)
	: QDialog(parent), scalesSpinBox(nullptr), testsSpinBox(nullptr), propertyEdit(nullptr), comboClassification(nullptr),
	buttonAccept(nullptr), buttonCancel(nullptr), kNeighborsSpinBox(nullptr),
	subdivisionsSpinBox(nullptr), strengthSpinBox(nullptr), layout(nullptr) {

	QLabel* labelScales = new QLabel(this);
	QLabel* labelTests = new QLabel(this);
	QLabel* labelClassification = new QLabel(this);
	QLabel* labelProperty = new QLabel(this);
	QLabel* labelRadiusNeighbors = new QLabel(this);
	QLabel* labelKNeighbors = new QLabel(this);
	QLabel* labelStrength = new QLabel(this);
	QLabel* labelSubdivisions = new QLabel(this);

	labelScales->setText("Number of scales");
	labelTests->setText("Number of tests");
	labelClassification->setText("Classification");
	labelProperty->setText("Property (float)");
	labelRadiusNeighbors->setText("Radius Neighbors");
	labelKNeighbors->setText("K-Neighbors");
	labelStrength->setText("Strength");
	labelSubdivisions->setText("Subdivisions");

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

	radiusNeighborsSpinBox = new QDoubleSpinBox(this);
	radiusNeighborsSpinBox->setRange(0, 100);
	radiusNeighborsSpinBox->setValue(radiusNeighbors);
	radiusNeighborsSpinBox->setEnabled(false);

	kNeighborsSpinBox = new QSpinBox(this);
	kNeighborsSpinBox->setRange(0, 100);
	kNeighborsSpinBox->setValue(kNeighbors);
	kNeighborsSpinBox->setEnabled(false);

	strengthSpinBox = new QDoubleSpinBox(this);
	strengthSpinBox->setRange(0, 100);
	strengthSpinBox->setValue(strength);
	strengthSpinBox->setEnabled(false);

	subdivisionsSpinBox = new QSpinBox(this);
	subdivisionsSpinBox->setRange(0, 100);
	subdivisionsSpinBox->setValue(subdivisions);
	subdivisionsSpinBox->setEnabled(false);

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
	addSeparator(4, 0);
	layout->addWidget(labelRadiusNeighbors, 5, 0);
	layout->addWidget(radiusNeighborsSpinBox, 5, 1);
	addSeparator(6, 0);
	layout->addWidget(labelKNeighbors, 7, 0);
	layout->addWidget(kNeighborsSpinBox, 7, 1);
	layout->addWidget(labelStrength, 8, 0);
	layout->addWidget(strengthSpinBox, 8, 1);
	layout->addWidget(labelSubdivisions, 9, 0);
	layout->addWidget(subdivisionsSpinBox, 9, 1);
	addSeparator(10, 0);
	layout->addWidget(buttonAccept, 11, 0);
	layout->addWidget(buttonCancel, 11, 1);
	setLayout(layout);
	
	connect(comboClassification, QOverload<int>::of(&QComboBox::activated), [=](int index)  { 
		QString selected = comboClassification->itemText(comboClassification->currentIndex()); 
		if (selected == QString(CLASSIFICATION_LOCAL_SMOOTHING)) {
			enableLocalSmoothing(true);
			enableGraphcut(false);
		}
		else if (selected == QString(CLASSIFICATION_GRAPHCUT)) {
			enableLocalSmoothing(false);
			enableGraphcut(true);
		}
		else {
			enableLocalSmoothing(false);
			enableGraphcut(false);
		}
	});
	connect(buttonAccept, SIGNAL(clicked()), this, SLOT(ok()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

TrainView::TrainView(const TrainView& trainView)
	: scalesSpinBox(trainView.scalesSpinBox), testsSpinBox(trainView.testsSpinBox), propertyEdit(trainView.propertyEdit), 
	comboClassification(trainView.comboClassification),buttonAccept(trainView.buttonAccept), buttonCancel(trainView.buttonCancel), 
	radiusNeighborsSpinBox(trainView.radiusNeighborsSpinBox), kNeighborsSpinBox(trainView.kNeighborsSpinBox),
	subdivisionsSpinBox(trainView.subdivisionsSpinBox), strengthSpinBox(trainView.strengthSpinBox), layout(trainView.layout) {
}


TrainView::TrainView(TrainView&& trainView) noexcept
	: scalesSpinBox(std::move(trainView.scalesSpinBox)), testsSpinBox(std::move(trainView.testsSpinBox)),
	propertyEdit(std::move(trainView.propertyEdit)), comboClassification(std::move(trainView.comboClassification)),
	buttonAccept(std::move(trainView.buttonAccept)), buttonCancel(std::move(trainView.buttonCancel)), 
	radiusNeighborsSpinBox(std::move(trainView.radiusNeighborsSpinBox)), kNeighborsSpinBox(std::move(trainView.kNeighborsSpinBox)),
	subdivisionsSpinBox(std::move(trainView.subdivisionsSpinBox)), strengthSpinBox(std::move(trainView.strengthSpinBox)),
	layout(std::move(trainView.layout)) {
}

void TrainView::enableLocalSmoothing(bool enable) {
	radiusNeighborsSpinBox->setEnabled(enable);
}

void TrainView::enableGraphcut(bool enable) {
	kNeighborsSpinBox->setEnabled(enable);
	strengthSpinBox->setEnabled(enable);
	subdivisionsSpinBox->setEnabled(enable);
}

void TrainView::addSeparator(int row, int col) {
	QFrame* line = new QFrame();
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	layout->addWidget(line, row, col, 1, 2);
}

void TrainView::ok() {
	accept();
	close();
}

void TrainView::cancel() {
	reject();
	close();
}