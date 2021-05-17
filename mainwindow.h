#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>
#include <vector>

#include <QMainWindow>
#include <QScrollArea>
#include <QListWidget>

#include "LabelView.h"
#include "FeatureView.h"
#include "EffectView.h"

#include "LabelView.h"
#include "FeatureView.h"
#include "EffectView.h"

class CCViewer3D;
class QAction;
class QToolBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
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
	QAction* actionAddFeature;
	QAction* actionAddEffect;
	QAction* actionDelete;
	QAction* actionRun;
	QToolBar* classifierToolBar;

	std::vector<LabelView*> labelViews;

	QListWidget* listWidgetLabels;
	QListWidget* listWidgetFeatures;
	QListWidget* listWidgetEffects;

	std::vector<std::string> comboLabelsVec;
	std::vector<std::string> comboFeaturesVec;

	QString filePath;
private:
	void initComponents();
	void initSignalsAndSlots();
	void initDocks();
	std::vector<LabelView*> getLabelViews();
	std::vector<FeatureView*> getFeatureViews();
	std::vector<EffectView*> getEffectViews();

	template <typename T>
	void addItem(QListWidget* listWidget, T* view);

	template <typename T>
	void deleteItem(QListWidget* listWidget, unsigned int id);
private:
	void resizeEffectListWidget();
	void resizeEvent(QResizeEvent* e);
	void changeEvent(QEvent* e);
private slots:
	void open();
	void addLabel();
	void addFeature();
	void deleteViews();
	void addEffects();
	void runModel();
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
};

#endif // MAINWINDOW_H