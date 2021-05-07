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
	input(nullptr), 
	analysis(nullptr), 
	featureManager(nullptr), 
	classifier(nullptr) {
		
	
	initComponents();
	initSignalsAndSlots();

	/*
	// Experimental
	std::string filePath = QFileDialog::getOpenFileName(this, tr("Open Point Cloud File"), "../Data", tr("PLY (*.ply)")).toLocal8Bit().constData();
	Input input(filePath);

	input.getLabelManager().createLabel("ground", CGAL::Color(122, 108, 99));
	input.getLabelManager().createLabel("vegetation", CGAL::Color(0, 255, 0));
	input.getLabelManager().createLabel("roof", CGAL::Color(255, 124, 0));

	float gridResolution = 0.1f; //float gridResolution = 0.34f;
	unsigned int numberOfNeighbors = 200;
	Analysis analysis(input, gridResolution, numberOfNeighbors);

	float radiusNeighbors = 0.1f; //float radiusNeighbors = 1.7f;
	float radiusDtm = 5.0f; //float radiusDtm = 15.0f;
	FeatureManager featureManager(analysis, radiusNeighbors, radiusDtm);

	Classifier classifier(featureManager);

	// Weights
	FeatureHandle distanceToPlane = featureManager.getDistanceToPlane();
	classifier.addWeight(WeightGroup(distanceToPlane, 6.75e-2f));

	FeatureHandle dispersion = featureManager.getDispersion();
	classifier.addWeight(WeightGroup(dispersion, 5.45e-1f));

	FeatureHandle elevation = featureManager.getElevation();
	classifier.addWeight(WeightGroup(elevation, 1.47e1f));

	// Labels
	LabelHandle ground = input.getLabelManager().getLabel("ground").handle;
	classifier.addEffect(EffectGroup(ground, distanceToPlane, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(ground, dispersion, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(ground, elevation, CGALclassifier::PENALIZING));

	LabelHandle vegetation = input.getLabelManager().getLabel("vegetation").handle;
	classifier.addEffect(EffectGroup(vegetation, distanceToPlane, CGALclassifier::FAVORING));
	classifier.addEffect(EffectGroup(vegetation, dispersion, CGALclassifier::FAVORING));
	classifier.addEffect(EffectGroup(vegetation, elevation, CGALclassifier::PENALIZING));

	LabelHandle roof = input.getLabelManager().getLabel("roof").handle;
	classifier.addEffect(EffectGroup(roof, distanceToPlane, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(roof, dispersion, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(roof, elevation, CGALclassifier::FAVORING));

	// Classify
	classifier.classify(ClassificationType::RAW);
	classifier.save();
	*/
}

MainWindow::~MainWindow() {
	if (input != nullptr) delete input;
	if (analysis != nullptr) delete analysis;
	if (featureManager != nullptr) delete featureManager;
	if (classifier != nullptr) delete classifier;
}

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
	this->addToolBar(Qt::TopToolBarArea, mToolBar3dModel);

	// Classifier tool bar
	classifierToolBar = new QToolBar(this);

	QIcon iconTag;
	iconTag.addFile(QStringLiteral(":/ico/icons/tag.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionAddLabel->setIcon(iconTag);

	classifierToolBar->addAction(actionAddLabel);
	addToolBar(Qt::TopToolBarArea, classifierToolBar);

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
}

void MainWindow::changeEvent(QEvent* e) {
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWindow::open() {
	ui->statusBar->showMessage(tr("Open Cloud Point File"));
	QString file = QFileDialog::getOpenFileName(this, tr("Open Point Cloud File"), "../Data", tr("PLY (*.ply)"));
	if (!file.isEmpty()) {
		mCCViewer3D->clear();
		mCCViewer3D->loadFromFile(file);
		mCCViewer3D->setGlobalZoom();
		input = new Input(file.toLocal8Bit().constData());
	}
}

void MainWindow::initDocks() {

	// Dock label
	listWidgetLabel = new QListWidget(this);
	ui->dockLabel->setWidget(listWidgetLabel);

	// Dock features

	// Dock effects
}

void MainWindow::addLabel() {

	static unsigned int index = 0;
	std::string labelName = "Label " + std::to_string(++index);
	LabelView* labelView = new LabelView(labelName, listWidgetLabel,"1");
	listWidgetLabel->setResizeMode(QListWidget::Adjust);
	QListWidgetItem* item = new QListWidgetItem(listWidgetLabel);
	item->setSizeHint(QSize(labelView->width(), labelView->height()));
	listWidgetLabel->setItemWidget(item, labelView);
}