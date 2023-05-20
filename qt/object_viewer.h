#ifndef QT_OBJECT_VIEWER_H_
#define QT_OBJECT_VIEWER_H_

extern "C" {
#include "../core/parser.h"
}
#include <QMouseEvent>
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

class Object_viewer : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public slots:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
 signals:
  void change_rotation(int rotation, char direction);

 protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

 public:
  Object_viewer();
  ~Object_viewer();
  char *filename_open;
  void init_facets();
  int rotation[3] = {0, 0, 0};
  int position[3] = {0, 0, 0};
  int projection = 0;
  double base_scale = 1;
  double new_scale = 1;
  void update_frame();
  void rotate_viewer(int angle, char direction);
  void scale_viewer(double scale);
  void move_viewer(int distance, char direction);
  struct object_s object = {0, 0, 0, 0, 0, 0, NULL, NULL, {0}};
  float *vert = NULL;
  unsigned int *facets = NULL;
  double prjn[6] = {-1.5, 1.5, -1.5, 1.5, -1.5, 1.5};

 private:
  void object_viewer_free();
  QPoint lastPos;
};
#endif  // QT_OBJECT_VIEWER_H_
