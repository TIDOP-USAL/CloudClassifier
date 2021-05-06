#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "Input.h"
#include "Analysis.h"
#include "FeatureManager.h"
#include "Classifier.h"

#include "Container.h"
#include "LabelView.h"

class CCViewer3D;
class QAction;
class QToolBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	Ui::MainWindow* ui;
	CCViewer3D* mCCViewer3D;
	QAction* mActionGlobalZoom;
	QAction* mActionViewFront;
	QAction* mActionViewTop;
	QAction* mActionViewLeft;
	QAction* mActionViewRight;
	QAction* mActionViewBack;
	QAction* mActionViewBottom;
	QToolBar* mToolBar3dModel;

	Container* containerLabel;
	QScrollArea* scrollAreaLabel;

	Input* input;
	Analysis* analysis;
	FeatureManager* featureManager;
	Classifier* classifier;
private:
	void initComponents();
	void initSignalsAndSlots();

	void initDockLabel();
	void addLabel();
protected:
	void changeEvent(QEvent* e);
protected slots:
	void open();
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
};

#endif // MAINWINDOW_H