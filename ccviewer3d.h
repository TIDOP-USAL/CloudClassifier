#ifndef VIEWER_3D_H
#define VIEWER_3D_H


#include <memory>

/* Qt */
#include <QObject>
#include <QOpenGLWidget>


/* CloudCompare */
#include "ccGLWindow.h"
#include <ccCameraSensor.h>


class CCViewer3D
  : public ccGLWindow
{

  Q_OBJECT

public:

  explicit CCViewer3D(QWidget *parent = nullptr);
  ~CCViewer3D();

  void clear();
  void createGroup(const QString &group, const QString &parent = QString());
  void deleteEntity(const QString &id);

  void loadFromFile(const QString &file, const QString &parent = QString());
  void loadFromFiles(const QStringList &files, const QString &parent = QString());
  void saveAs(const QString &file);

  void setScale(double x, double y);


public slots:

  void deleteSelectEntity();

  /* Vistas por defecto */
  void setFrontView();
  void setBottomView();
  void setTopView();
  void setBackView();
  void setLeftView();
  void setRightView();
  void setIsoView1();
  void setIsoView2();
  void setGlobalZoom();

  void setVisible(const QString &id, bool visible);

protected slots:

  /*!
   * \brief selecciona una entidad
   */
  void selectEntity(ccHObject *entity);

private:

  void init();

  void addToDB(ccHObject *entity);

  /*!
   * \brief Función para buscar un objeto mediante su nombre
   */
  ccHObject *findChild(const QString &name, ccHObject *parent = nullptr);

private:

  ccHObject *mSelectedObject;
  double mScaleX;
  double mScaleY;
  std::map<QString, ccCameraSensor *> mCameras;

};


#endif // VIEWER_3D_H
