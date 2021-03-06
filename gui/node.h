#ifndef NODE_H
#define NODE_H

#include <mapper/mapper_db.h>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOption>

#include <cstdio>

#include <QGraphicsItem>
#include <QLabel>
#include <QStandardItem>

class Form;
class Node;

/*
class qt_mapping : public _mapper_db_mapping {

public:
    Node* destination_node;

};
*/

typedef struct _qt_mapping {

    Node* destination_node;

    char* src_name;
    char* dest_name;

    char src_type;
    char dest_type;

    mapper_clipping_type clip_max;
    mapper_clipping_type clip_min;

    mapper_mapping_range_t range;
    char* expression;

    mapper_mode_type mode;

    int muted;

} *qt_mapping;

class Node : public QObject, public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES( QGraphicsItem )

public:
    Node(QGraphicsView* graphWidget);
    ~Node();

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget);

    void setName( const char* new_name );

    QList<QStandardItem*> source_model_list;
    QList<QStandardItem*> dest_model_list;

    void addMapping( Node* destination,
                    const char* source_signal_name,
                    const char* destination_signal_name,
                    qt_mapping mapping );
    void removeMapping( Node* destination,
                    const char* source_signal_name,
                    const char* destination_signal_name );

    bool is_source;
    bool is_destination;
    int conflict_flag; //-1 => source, 0 => no confict, 1 => destination

    const char* name;

    int inputs;
    int outputs;
    int diameter;
    int sides;
    float concavity;
    int r;
    int g;
    int b;

    std::list<qt_mapping> destination_list;

signals:
    void selectionStateChanged( bool is_selected );

    void nodePressed( Node* reference );
    void nodeReleased( Node* reference );

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    //QList<Link*> linkList;

    QPointF newPos;
    QGraphicsView *graph;

    QGraphicsSimpleTextItem name_item;
    QGraphicsSimpleTextItem input_num_item;
    QGraphicsSimpleTextItem output_num_item;

};

#endif // NODE_H
