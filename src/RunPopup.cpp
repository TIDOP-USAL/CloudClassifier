#include "RunPopup.h"

#include <QLabel>

RunPopup::RunPopup(QWidget* parent) 
	: QDialog(parent), layout(nullptr), spinGridResolution(nullptr), spinNumberOfNeighbors(nullptr), spinRadiusNeighbors(nullptr),
	spinRadiusDtm(nullptr), strengthSpinBox(nullptr), kNeighborsSpinBox(nullptr), subdivisionsSpinBox(nullptr),
	comboClassification(nullptr), buttonAccept(nullptr), buttonCancel(nullptr) {
}

RunPopup::RunPopup(QWidget* parent, float gridResolution, unsigned int numberOfNeighbors, 
	float radiusNeighbors, float radiusDtm, unsigned int kNeighbors, double strength, unsigned int subdivisions)
	: QDialog(parent), layout(nullptr), spinGridResolution(nullptr), spinNumberOfNeighbors(nullptr), spinRadiusNeighbors(nullptr),
	spinRadiusDtm(nullptr), strengthSpinBox(nullptr), kNeighborsSpinBox(nullptr), subdivisionsSpinBox(nullptr),
	comboClassification(nullptr), buttonAccept(nullptr), buttonCancel(nullptr) {

	setWindowTitle(tr(RUN_POPUP_TITLE));
	setWindowModality(Qt::ApplicationModal);
	setModal(true);

	QLabel* labelGridResolution = new QLabel(this);
	QLabel* labelNumberOfNeighbors = new QLabel(this);
	QLabel* labelRadiusNeighbors = new QLabel(this);
	QLabel* labelRadiusDtm = new QLabel(this);
	QLabel* labelClassification = new QLabel(this);

	QLabel* labelKNeighbors = new QLabel(this);
	QLabel* labelStrength = new QLabel(this);
	QLabel* labelSubdivisions = new QLabel(this);

	labelGridResolution->setText("Grid resolution");
	labelNumberOfNeighbors->setText("Number of neighbors");
	labelRadiusNeighbors->setText("Radius neighbors");
	labelRadiusDtm->setText("Radius dtm");
	labelClassification->setText("Label classification");

	labelKNeighbors->setText("K-Neighbors");
	labelStrength->setText("Strength");
	labelSubdivisions->setText("Subdivisions");

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
	addSeparator(5, 0);
	layout->addWidget(labelKNeighbors, 6, 0);
	layout->addWidget(kNeighborsSpinBox, 6, 1);
	layout->addWidget(labelStrength, 7, 0);
	layout->addWidget(strengthSpinBox, 7, 1);
	layout->addWidget(labelSubdivisions, 8, 0);
	layout->addWidget(subdivisionsSpinBox, 8, 1);
	addSeparator(9, 0);
	layout->addWidget(buttonAccept, 10, 0);
	layout->addWidget(buttonCancel, 10, 1);

	setLayout(layout);

	connect(comboClassification, QOverload<int>::of(&QComboBox::activated), [=](int index) {
		QString selected = comboClassification->itemText(comboClassification->currentIndex());
		if (selected == QString(CLASSIFICATION_GRAPHCUT))
			enableGraphcut(true);
		else
			enableGraphcut(false);
	});
	connect(buttonAccept, SIGNAL(clicked()), this, SLOT(ok()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

RunPopup::RunPopup(const RunPopup& runPopup) 
	: layout(runPopup.layout), spinGridResolution(runPopup.spinGridResolution), spinNumberOfNeighbors(runPopup.spinNumberOfNeighbors), 
	spinRadiusNeighbors(runPopup.spinRadiusNeighbors), spinRadiusDtm(runPopup.spinRadiusDtm), strengthSpinBox(runPopup.strengthSpinBox),
	kNeighborsSpinBox(runPopup.kNeighborsSpinBox), subdivisionsSpinBox(runPopup.subdivisionsSpinBox), comboClassification(runPopup.comboClassification),
	buttonAccept(runPopup.buttonAccept), buttonCancel(runPopup.buttonCancel) {
}

RunPopup::RunPopup(RunPopup&& runPopup) noexcept
	: layout(std::move(runPopup.layout)), spinGridResolution(std::move(runPopup.spinGridResolution)), spinNumberOfNeighbors(std::move(runPopup.spinNumberOfNeighbors)),
	spinRadiusNeighbors(std::move(runPopup.spinRadiusNeighbors)), spinRadiusDtm(std::move(runPopup.spinRadiusDtm)), strengthSpinBox(std::move(runPopup.strengthSpinBox)),
	kNeighborsSpinBox(std::move(runPopup.kNeighborsSpinBox)), subdivisionsSpinBox(std::move(runPopup.subdivisionsSpinBox)), comboClassification(std::move(runPopup.comboClassification)),
	buttonAccept(std::move(runPopup.buttonAccept)), buttonCancel(std::move(runPopup.buttonCancel)) {
}

void RunPopup::enableGraphcut(bool enable) {
	kNeighborsSpinBox->setEnabled(enable);
	strengthSpinBox->setEnabled(enable);
	subdivisionsSpinBox->setEnabled(enable);
}

void RunPopup::addSeparator(int row, int col) {
	QFrame* line = new QFrame(this);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	layout->addWidget(line, row, col, 1, 2);
}

void RunPopup::ok() {
	accept();
	close();
}

void RunPopup::cancel() {
	reject();
	close();
}