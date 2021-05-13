#include "RunPopup.h"

#include <QLabel>

RunPopup::RunPopup(QWidget* parent) 
	: QDialog(parent) {
}

RunPopup::RunPopup(QWidget* parent, float gridResolution, unsigned int numberOfNeighbors, float radiusNeighbors, float radiusDtm) 
{

	setWindowTitle(tr(RUN_POPUP_TITLE));
	setWindowModality(Qt::ApplicationModal);
	setModal(true);

	QLabel* labelGridResolution = new QLabel(this);
	QLabel* labelNumberOfNeighbors = new QLabel(this);
	QLabel* labelRadiusNeighbors = new QLabel(this);
	QLabel* labelRadiusDtm = new QLabel(this);
	QLabel* labelClassification = new QLabel(this);

	labelGridResolution->setText("Grid resolution");
	labelNumberOfNeighbors->setText("Number of neighbors");
	labelRadiusNeighbors->setText("Radius neighbors");
	labelRadiusDtm->setText("Radius dtm");
	labelClassification->setText("Label classification");

	spinGridResolution = new QDoubleSpinBox(this);
	spinGridResolution->setRange(0, 2);
	spinGridResolution->setValue(gridResolution);

	spinNumberOfNeighbors = new QDoubleSpinBox(this);
	spinNumberOfNeighbors->setRange(0, 999);
	spinNumberOfNeighbors->setValue(numberOfNeighbors);

	spinRadiusNeighbors = new QDoubleSpinBox(this);
	spinRadiusNeighbors->setRange(0, 2);
	spinRadiusNeighbors->setValue(radiusNeighbors);

	spinRadiusDtm = new QDoubleSpinBox(this);
	spinRadiusDtm->setRange(0, 5);
	spinRadiusDtm->setValue(radiusDtm);

	comboClassification = new QComboBox(this);
	comboClassification->addItem(CLASSIFICATION_RAW);
	comboClassification->addItem(CLASSIFICATION_LOCAL_SMOOTHING);
	comboClassification->addItem(CLASSIFICATION_GRAPHCUT);

	buttonAccept = new QPushButton(this);
	buttonAccept->setText("Accept");

	buttonCancel = new QPushButton(this);
	buttonCancel->setText("Cancel");

	layout = new QGridLayout(this);
	layout->addWidget(labelGridResolution, 0, 0);
	layout->addWidget(spinGridResolution, 0, 1);
	layout->addWidget(labelNumberOfNeighbors, 1, 0);
	layout->addWidget(spinNumberOfNeighbors, 1, 1);
	layout->addWidget(labelRadiusNeighbors, 2, 0);
	layout->addWidget(spinRadiusNeighbors, 2, 1);
	layout->addWidget(labelRadiusDtm, 3, 0);
	layout->addWidget(spinRadiusDtm, 3, 1);
	layout->addWidget(labelClassification, 4, 0);
	layout->addWidget(comboClassification, 4, 1);
	layout->addWidget(buttonAccept, 5, 0);
	layout->addWidget(buttonCancel, 5, 1);

	setLayout(layout);

	connect(comboClassification, QOverload<int>::of(&QComboBox::activated), [=](int index) { comboClassification->itemText(comboClassification->currentIndex()); });
	connect(buttonAccept, SIGNAL(clicked()), this, SLOT(ok()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

void RunPopup::ok() {
	accept();
	close();
}

void RunPopup::cancel() {
	reject();
	close();
}