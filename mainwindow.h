#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QListWidget>

#include "Input.h"
#include "Analysis.h"
#include "FeatureManager.h"
#include "Classifier.h"

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

	QAction* actionAddLabel;
	QToolBar* classifierToolBar;

	QListWidget* listWidgetLabel;

	Input* input;
	Analysis* analysis;
	FeatureManager* featureManager;
	Classifier* classifier;
private:
	void initComponents();
	void initSignalsAndSlots();

	void initDocks();
protected:
	void changeEvent(QEvent* e);
protected slots:
	void open();
	void addLabel();
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
};

#endif // MAINWINDOW_H