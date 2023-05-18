#include "object_viewer.h"

Object_viewer::Object_viewer() { ;
}

//  деструктор освобождаем выделенную память
Object_viewer::~Object_viewer() {
    object_viewer_free();
}

void Object_viewer::object_viewer_free() {
    if(vert) free(vert);
    if(facets) free(facets);
    free_object(&object);
}

void Object_viewer::init_facets() {

    object_viewer_free(); //  освобождаем памяь и обнуляем все значения в структуре
    int error = parse_file(filename_open, &object);
    if(error == 0) {
        facets = get_facets(&object);
        vert = get_vertices(&object);
        //normalize_vertices(vert, &object);
        //print_object(object);
        update_frame();
    } else {
        printf("%s", view_error(error));
    }
}

void Object_viewer::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void Object_viewer::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
}

void Object_viewer::update_frame() {
    update();
}

void Object_viewer::paintGL() {
    // projection
    double * p = get_projection(object);
    //print_object(object);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(p[0], p[1], p[2], p[3], p[4], p[5]);
    glTranslated(0, 0, -p[4]*2);
    //glOrtho(p[0], p[1], p[2], p[3], -p[4], p[5]);
    //glOrtho(object.minMax[0], object.minMax[1], object.minMax[2], object.minMax[3], -object.minMax[4], object.minMax[5]);
    //glOrtho(-1,1,-1,1,-1,1);

    // draw
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vert);
    glDrawElements(GL_LINES, object.facets_limit, GL_UNSIGNED_INT, facets);
    glDisableClientState(GL_VERTEX_ARRAY);
    free(p);
}



void Object_viewer::rotate_viewer(int angle, char direction) {
    int current_rotation = (direction == 'x') ? rotation[0] : (direction == 'y') ? rotation[1] : (direction == 'z') ? rotation[2] : '0';
    rotate(vert, &object, angle - current_rotation, direction);
    if(direction == 'x') rotation[0] = angle;
    if(direction == 'y') rotation[1] = angle;
    if(direction == 'z') rotation[2] = angle;
    update_frame();
}

void Object_viewer::scale_viewer(int scale) {
    double new_scale = 1 + (double)scale / 100;
    scale_object(vert, &object, base_scale, new_scale);
    update_frame();
    base_scale = new_scale;
}

void Object_viewer::move_viewer(int distance, char direction) {
    int current_position = (direction == 'x') ? position[0] : (direction == 'y') ? position[1] : (direction == 'z') ? position[2] : '0';
    move_object(vert, &object, distance - current_position, direction);
    if(direction == 'x') position[0] = distance;
    if(direction == 'y') position[1] = distance;
    if(direction == 'z') position[2] = distance;
    update_frame();
}

void Object_viewer::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void Object_viewer::mouseMoveEvent(QMouseEvent *event) {
    int dx = event->position().x() - lastPos.x();
    int dy = event->position().y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotate(vert, &object, dy, 'x');
        rotate(vert, &object, dx, 'y');
        rotation[0] += dy;
        rotation[1] += dx;
    }

    lastPos = event->pos();
    update_frame();
}
