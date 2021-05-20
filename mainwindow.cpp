#include <thread>

#include <QComboBox>
#include <QDialog>
#include <QDockWidget>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QScrollArea>
#include <QToolBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ccviewer3d.h"

#include "LabelController.h"
#include "FeatureController.h"
#include "EffectController.h"
#include "ClassificationModel.h"

#include "RunPopup.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), 
	mActionGlobalZoom(new QAction(this)), 
	mActionViewFront(new QAction(this)),
	mActionViewTop(new QAction(this)), 
	mActionViewLeft(new QAction(this)), 
	mActionViewRight(new QAction(this)), 
	mActionViewBack(new QAction(this)),
	mActionViewBottom(new QAction(this)),
	actionAddLabel(new QAction(this)),
	actionAddFeature(new QAction(this)),
	actionAddEffect(new QAction(this)),
	actionTrain(new QAction(this)),
	actionDelete(new QAction(this)),
	actionRun(new QAction(this)) {
	
	initComponents();
	initSignalsAndSlots();
}

MainWindow::~MainWindow() { }

void MainWindow::initComponents() {

	// UI
	ui->setupUi(this);
	this->setWindowTitle(tr("TIDOP Point Cloud Classifier"));
	ui->statusBar->showMessage(tr("TIDOP Point Cloud Classifier"));

	// Layout
	QGridLayout *layoutCentral = new QGridLayout(this->centralWidget());
	layoutCentral->setSpacing(6);
	layoutCentral->setContentsMargins(0,0,0,0);

	// Add CCViewer
	mCCViewer3D = new CCViewer3D;
	layoutCentral->addWidget(mCCViewer3D,0,0);

	// Main tool bar buttons
	QIcon iconOpen;
	iconOpen.addFile(QStringLiteral(":/ico/icons/icons8-open.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->actionOpen->setIcon(iconOpen);
	QIcon iconSave;
	iconSave.addFile(QStringLiteral(":/ico/icons/icons8-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->actionSaveAs->setIcon(iconSave);

	// Viewer tool bar buttons
	QIcon iconGlobalZoom;
	iconGlobalZoom.addFile(QStringLiteral(":/ico/icons/icons8-magnifying-glass-with-expand-sign.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionGlobalZoom->setIcon(iconGlobalZoom);
	QIcon iconViewFront;
	iconViewFront.addFile(QStringLiteral(":/ico/icons/icons8-front-view.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionViewFront->setIcon(iconViewFront);
	QIcon iconViewTop;
	iconViewTop.addFile(QStringLiteral(":/ico/icons/icons8-top-view.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionViewTop->setIcon(iconViewTop);
	QIcon iconViewLeft;
	iconViewLeft.addFile(QStringLiteral(":/ico/icons/icons8-cube.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionViewLeft->setIcon(iconViewLeft);
	QIcon iconViewRight;
	iconViewRight.addFile(QStringLiteral(":/ico/icons/icons8-view_right.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionViewRight->setIcon(iconViewRight);
	QIcon iconViewBack;
	iconViewBack.addFile(QStringLiteral(":/ico/icons/icons8-back-view.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionViewBack->setIcon(iconViewBack);
	QIcon iconViewBottom;
	iconViewBottom.addFile(QStringLiteral(":/ico/icons/icons8-bottom-view.png"), QSize(), QIcon::Normal, QIcon::Off);
	mActionViewBottom->setIcon(iconViewBottom);

	// Main tool bar
	ui->mainToolBar->setToolTip(tr("Main Tools"));
	ui->mainToolBar->setStatusTip(tr("Main Tools"));
	ui->mainToolBar->addAction(ui->actionOpen);
	ui->mainToolBar->addAction(ui->actionSaveAs);

	// Viewer tool bar
	mToolBar3dModel = new QToolBar(this);
	mToolBar3dModel->setMovable(false);
	mToolBar3dModel->setOrientation(Qt::Orientation::Vertical);

	mToolBar3dModel->setToolTip(tr("Viewing Tools"));
	mToolBar3dModel->setStatusTip(tr("Viewing Tools"));
	mToolBar3dModel->setObjectName("ToolBar3dModel");
	mToolBar3dModel->addAction(mActionGlobalZoom);
	mToolBar3dModel->addSeparator();
	mToolBar3dModel->addAction(mActionViewFront);
	mToolBar3dModel->addAction(mActionViewBack);
	mToolBar3dModel->addAction(mActionViewTop);
	mToolBar3dModel->addAction(mActionViewBottom);
	mToolBar3dModel->addAction(mActionViewLeft);
	mToolBar3dModel->addAction(mActionViewRight);
	this->addToolBar(Qt::RightToolBarArea, mToolBar3dModel);

	// Classifier tool bar
	classifierToolBar = new QToolBar(this);
	classifierToolBar->setMovable(false);
	classifierToolBar->setOrientation(Qt::Orientation::Vertical);

	QIcon iconTag;
	iconTag.addFile(QStringLiteral(":/ico/icons/tag.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionAddLabel->setIcon(iconTag);

	QIcon iconFeature;
	iconFeature.addFile(QStringLiteral(":/ico/icons/feature.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionAddFeature->setIcon(iconFeature);

	QIcon iconEffect;
	iconEffect.addFile(QStringLiteral(":/ico/icons/effect.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionAddEffect->setIcon(iconEffect);

	QIcon iconTrain;
	iconTrain.addFile(QStringLiteral(":/ico/icons/train.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionTrain->setIcon(iconTrain);

	classifierToolBar->addAction(actionAddLabel);
	classifierToolBar->addAction(actionAddFeature);
	classifierToolBar->addAction(actionAddEffect);
	classifierToolBar->addSeparator();
	classifierToolBar->addAction(actionTrain);
	addToolBar(Qt::LeftToolBarArea, classifierToolBar);

	// Run tool bar
	runToolBar = new QToolBar(this);
	runToolBar->setMovable(false);
	runToolBar->setOrientation(Qt::Orientation::Vertical);

	QIcon iconDelete;
	iconDelete.addFile(QStringLiteral(":/ico/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionDelete->setIcon(iconDelete);

	QIcon iconRun;
	iconRun.addFile(QStringLiteral(":/ico/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionRun->setIcon(iconRun);

	runToolBar->addAction(actionDelete);
	runToolBar->addAction(actionRun);
	addToolBar(Qt::TopToolBarArea, runToolBar);

	// Dock Label
	initDocks();
}

void MainWindow::initSignalsAndSlots() {
	//Menu file
	connect(ui->actionOpen,   &QAction::triggered, this, &MainWindow::open);
	// Viewer tool bar
	connect(mActionGlobalZoom, SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setGlobalZoom()));
	connect(mActionViewFront,  SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setFrontView()));
	connect(mActionViewBack,   SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setBackView()));
	connect(mActionViewTop,    SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setTopView()));
	connect(mActionViewBottom, SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setBottomView()));
	connect(mActionViewLeft,   SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setLeftView()));
	connect(mActionViewRight,  SIGNAL(triggered(bool)), mCCViewer3D, SLOT(setRightView()));
	// Classifier tool bar
	connect(actionAddLabel, SIGNAL(triggered(bool)), this, SLOT(addLabel()));
	connect(actionAddFeature, SIGNAL(triggered(bool)), this, SLOT(addFeature()));
	connect(actionAddEffect, SIGNAL(triggered(bool)), this, SLOT(addEffects()));
	connect(actionTrain, SIGNAL(triggered(bool)), this, SLOT(runTraining()));
	connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(deleteViews()));
	connect(actionRun, SIGNAL(triggered(bool)), this, SLOT(runModel()));
}

void MainWindow::initDocks() {
	// Dock label
	listWidgetLabels = new QListWidget(this);
	listWidgetLabels->setResizeMode(QListWidget::Adjust);
	listWidgetLabels->setSelectionMode(QAbstractItemView::MultiSelection);
	ui->dockLabel->setWidget(listWidgetLabels);
	// Dock features
	listWidgetFeatures = new QListWidget(this);
	listWidgetFeatures->setResizeMode(QListWidget::Adjust);
	listWidgetFeatures->setSelectionMode(QAbstractItemView::MultiSelection);
	ui->dockFeatures->setWidget(listWidgetFeatures);
	// Dock effects
	listWidgetEffects = new QListWidget(this);
	listWidgetEffects->setResizeMode(QListWidget::Adjust);
	listWidgetEffects->setSelectionMode(QAbstractItemView::NoSelection);
	ui->dockEffects->setWidget(listWidgetEffects);

}

std::vector<LabelView*> MainWindow::getLabelViews() {
	std::vector<LabelView*> labelViews;
	for (int i = 0; i < listWidgetLabels->count(); i++) {
		QListWidgetItem* item = listWidgetLabels->item(i);
		LabelView* labelView = dynamic_cast<LabelView*>(listWidgetLabels->itemWidget(item));
		labelViews.push_back(labelView);
	}
	return labelViews;
}

std::vector<FeatureView*> MainWindow::getFeatureViews() {
	std::vector<FeatureView*> featureViews;
	for (int i = 0; i < listWidgetFeatures->count(); i++) {
		QListWidgetItem* item = listWidgetFeatures->item(i);
		FeatureView* featureView = dynamic_cast<FeatureView*>(listWidgetFeatures->itemWidget(item));
		featureViews.push_back(featureView);
	}
	return featureViews;
}

std::vector<EffectView*> MainWindow::getEffectViews() {
	std::vector<EffectView*> effectViews;
	for (int i = 0; i < listWidgetEffects->count(); i++) {
		QListWidgetItem* item = listWidgetEffects->item(i);
		EffectView* effectView = dynamic_cast<EffectView*>(listWidgetEffects->itemWidget(item));
		effectViews.push_back(effectView);
	}
	return effectViews;
}

void MainWindow::resizeEffectListWidget() {
	for (int i = 0; i < listWidgetEffects->count(); i++) {
		QListWidgetItem* item = listWidgetEffects->item(i);
		EffectView* effectView = dynamic_cast<EffectView*>(listWidgetEffects->itemWidget(item));
		effectView->updateSize();
	}
}

void MainWindow::resizeEvent(QResizeEvent* e) {
	QMainWindow::resizeEvent(e);
	resizeEffectListWidget();
}

void MainWindow::changeEvent(QEvent* e) {
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	}
}

void MainWindow::open() {
	ui->statusBar->showMessage(tr("Open Cloud Point File"));
	filePath = QFileDialog::getOpenFileName(this, tr("Open Point Cloud File"), "../Data", tr("PLY (*.ply)"));
	if (!filePath.isEmpty()) {
		mCCViewer3D->clear();
		mCCViewer3D->loadFromFile(filePath);
		mCCViewer3D->setGlobalZoom();
	}
}

template <typename T>
void MainWindow::addItem(QListWidget* listWidget, T* view) {
	QListWidgetItem* item = new QListWidgetItem(listWidget);
	item->setSizeHint(QSize(view->width(), view->height()));
	listWidget->setItemWidget(item, view);
}

template <typename T>
void MainWindow::deleteItem(QListWidget* listWidget, unsigned int id) {
	for (int i = 0; i < listWidget->count(); i++) {
		QListWidgetItem* item = listWidget->item(i);
		T* view = dynamic_cast<T*>(listWidget->itemWidget(item));
		if (view->getID() == id) {
			delete item;
			break;
		}
	}
}

void MainWindow::addLabel() {
	// Create view
	static unsigned int index = 0;
	unsigned int deleteIndex = index;
	std::string labelName = "Label " + std::to_string(index);
	LabelView* labelView = new LabelView(index, labelName, listWidgetLabels, labelName.c_str());
	// Add view
	addItem<LabelView>(listWidgetLabels, labelView);
	// Remove label
	connect(labelView, &LabelView::deleteSignal, [&](unsigned int id) {
		deleteItem<LabelView>(listWidgetLabels, id);
	});
	index++;
}

void MainWindow::addFeature() {
	// Create view
	static unsigned int index = 0;
	std::string featureName = "Feature " + std::to_string(index);
	FeatureView* featureView = new FeatureView(index, listWidgetFeatures, featureName.c_str());
	// Add view
	addItem<FeatureView>(listWidgetFeatures, featureView);
	// Remove Feature
	connect(featureView, &FeatureView::deleteSignal, [&](unsigned int id) {
		deleteItem<FeatureView>(listWidgetFeatures, id);
	});
	index++;
}

void MainWindow::deleteViews() {
	for (QListWidgetItem* item : listWidgetLabels->selectedItems())
		delete item;
	for (QListWidgetItem* item : listWidgetFeatures->selectedItems())
		delete item;
}

void MainWindow::addEffects() {
	// Get label names
	comboLabelsVec.clear();
	for (int i = 0; i < listWidgetLabels->count(); i++) {
		QListWidgetItem* item = listWidgetLabels->item(i);
		LabelView* labelView = dynamic_cast<LabelView*>(listWidgetLabels->itemWidget(item));
		QString text = labelView->getText();
		comboLabelsVec.push_back(text.toLocal8Bit().constData());
	}
	// Get feature names
	comboFeaturesVec.clear();
	for (int i = 0; i < listWidgetFeatures->count(); i++) {
		QListWidgetItem* item = listWidgetFeatures->item(i);
		FeatureView* featureView = dynamic_cast<FeatureView*>(listWidgetFeatures->itemWidget(item));
		QString name = featureView->getFeatureName();
		comboFeaturesVec.push_back(name.toLocal8Bit().constData());
	}
	// Create effects
	listWidgetEffects->clear();
	for (std::string& labelName : comboLabelsVec) {
		static int colorIndex = 0;
		for (std::string& featureName : comboFeaturesVec) {
			static unsigned int index = 0;
			std::string effectName = "Effect " + std::to_string(++index);
			EffectView* effectView = new EffectView(comboLabelsVec, comboFeaturesVec, listWidgetEffects, effectName.c_str());
			effectView->getComboBoxLabels()->setCurrentText(QString(labelName.c_str()));
			effectView->getComboBoxFeatures()->setCurrentText(QString(featureName.c_str()));
			// Add view
			QListWidgetItem* item = new QListWidgetItem(listWidgetEffects);
			item->setSizeHint(QSize(effectView->width(), effectView->height()));
			int color = 1 / 3 * 255 + (colorIndex % 2) * 255 * 2 / 3;
			int alpha = 50;
			item->setBackgroundColor(QColor(color, 120, 255, alpha));
			listWidgetEffects->setItemWidget(item, effectView);
		}
		colorIndex++;
	}
}

void MainWindow::runModel() {
	// Classification variables
	float gridResolution = 0.1f;
	unsigned int numberOfNeighbors = 200;
	float radiusNeighbors = 0.1f;
	float radiusDtm = 5.0f;
	ClassificationType classificationType = ClassificationType::NONE;
	// Run popup
	RunPopup* runPopup = new RunPopup(this, gridResolution, numberOfNeighbors, radiusNeighbors, radiusDtm);
	if (runPopup->exec() != QDialog::Accepted)
		return;
	// Get new variables
	gridResolution = runPopup->getGridResolution();
	numberOfNeighbors = runPopup->getNumberOfNeighbors();
	radiusNeighbors = runPopup->getRadiusNeighbors();
	radiusDtm = runPopup->getRadiusDtm();
	QString classificationStr = runPopup->getClassificationType();
	if (classificationStr == QString(CLASSIFICATION_RAW))						classificationType = ClassificationType::RAW;
	else if (classificationStr == QString(CLASSIFICATION_LOCAL_SMOOTHING))		classificationType = ClassificationType::LOCAL_SMOOTHING;
	else if (classificationStr == QString(CLASSIFICATION_GRAPHCUT))				classificationType = ClassificationType::GRAPHCUT;
	else																		classificationType = ClassificationType::NONE;
	// Controllers
	LabelController labelController(getLabelViews());
	FeatureController featureController(getFeatureViews());
	EffectController effectController(getEffectViews());
	// Model
	std::string path = filePath.toLocal8Bit().constData();
	ClassificationModel classificationModel(path, labelController, featureController, effectController);
	classificationModel.run(gridResolution, numberOfNeighbors, radiusNeighbors, radiusDtm, classificationType);
}

void MainWindow::runTraining() {

	std::vector<LabelView*> labelViews = getLabelViews();
	if (labelViews.empty()) {
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("No labels");
		msgBox.exec();
		return;
	}



	//TrainController(labelViews, trainView);
}