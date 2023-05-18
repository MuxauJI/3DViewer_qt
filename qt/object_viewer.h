#ifndef OBJECT_VIEWER_H
#define OBJECT_VIEWER_H

extern "C" {
#include "../core/parser.h"
}
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
//#include <QtGlobal>

class Object_viewer : QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public:
    Object_viewer();
    ~Object_viewer();
    char *filename_open;
    void init_facets();
    int rotation[3] = {0, 0, 0};
    int position[3] = {0, 0, 0};
    double base_scale = 1;
    void update_frame();
    void rotate_viewer(int angle, char direction);
    void scale_viewer(int scale);
    void move_viewer(int distance, char direction);
    struct object_s object = {0, 0, 0, 0, 0, 0, NULL, NULL, {0}};
    float * vert = NULL;
    unsigned int * facets = NULL;
    double prjn[6] = {-1.5,1.5,-1.5,1.5,-1.5,1.5};
private:


    void object_viewer_free();
    QPoint lastPos;
};
#endif // OBJECT_VIEWER_H
