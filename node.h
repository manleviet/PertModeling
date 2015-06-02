#ifndef NODE_H
#define NODE_H

#include <QColor>
#include <QGraphicsEllipseItem>
#include "task.h"

class DiagramScene;
class Task;

class Node : public QGraphicsEllipseItem
{
public:
    enum {Type = UserType +15};
    int type() const {return Type;}

    enum State {Normal, Aller, Retour, ChangeAller, ChangeRetour};
    State state() {return _state;}
    void setState(State state) {_state = state;}

    Node(float x, float y, const QString &id);

    QString &id() {return _id;}
    void setEarlyDate(const QString &earlyDate) {_earlyDate = earlyDate;}
    QString earlyDate() {return this->_earlyDate;}
    void setLateDate(const QString &lateDate) {_lateDate = lateDate;}
    QString lateDate() {return this->_lateDate;}
    void addTask(Task *task);
    QPolygonF polygon() const { return myPolygon; }

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString _id;
    QString _earlyDate;
    QString _lateDate;
    QList<Task *> tasks;
    QPolygonF myPolygon;
    State _state;
};

#endif // NODE_H
