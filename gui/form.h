#ifndef FORM_H
#define FORM_H

#include <list>

#include <QTimer>

#include <mapper/mapper.h>

#include "ui_form.h"
#include "edge.h"
#include "node.h"

class Form : public QWidget, private Ui::Form
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

    void itemMoved();
    void addNode();

    //int (*createTestDeviceFunction)();
    void addNewDevice( const char* name );
    void addDbCallbackFunction( device_callback_func* f );
    void setMapperDevice( mapper_device device );

public slots:
    void update();

protected:
    void keyPressEvent(QKeyEvent *event);
    //void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    //void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    std::list <Node*> node_pointer_list;
    QGraphicsScene* scene;

    QTimer* timer;
    device_callback_func* db_callback_function;
    mapper_device qtmapper;
};

#endif // FORM_H