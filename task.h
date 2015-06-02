#ifndef TASK_H
#define TASK_H

#include <QGraphicsLineItem>

#include "node.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
class Node;
QT_END_NAMESPACE

class Task : public QGraphicsLineItem
{
public:
    enum TypeTask { TaskNormal, TaskFictive };

    enum State {Normal, Aller, Retour, Fin};
    State state() {return _state;}
    void setState(State state) {_state = state;}

    Task(TypeTask typeTask, Node *start, Node *end,
         const QString &id, int weight,
         QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    TypeTask typeTask() { return myTypeTask; }
    Node *start() const { return startNode; }
    Node *end() const { return endNode; }
    QString &id() { return _id; }
    int weight() { return _weight; }
    void updatePosition();

    QString slack() {return _slack;}
    void setSlack(const QString slack) {_slack = slack;}

    bool critique() {return isCritique;}
    void setCritique(bool critique) {isCritique = critique;}

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    TypeTask myTypeTask;
    QString _id;
    int _weight;
    Node *startNode;
    Node *endNode;
    QPolygonF arrowHead;
    State _state;
    QString _slack;
    bool isCritique;
};

#endif // TASK_H
