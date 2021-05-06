#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "Classifier.h"

#include "Container.h"

class CCViewer3D;
class QAction;
class QToolBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	protected:
		void changeEvent(QEvent *e);

	protected slots:
		void open();

	private:
		void initComponents();
		void initSignalsAndSlots();
		void initDockLabel();

	private:
		Ui::MainWindow *ui;
		CCViewer3D *mCCViewer3D;
		QAction *mActionGlobalZoom;
		QAction *mActionViewFront;
		QAction *mActionViewTop;
		QAction *mActionViewLeft;
		QAction *mActionViewRight;
		QAction *mActionViewBack;
		QAction *mActionViewBottom;
		QToolBar *mToolBar3dModel;

		Container* containerLabel;
		QScrollArea* scrollAreaLabel;
};

#endif // MAINWINDOW_H