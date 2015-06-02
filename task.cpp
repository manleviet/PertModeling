#include <QtGui>
#include <QColor>
#include <math.h>

#include "task.h"

const qreal Pi = 3.14;
const qreal TwoPi = 2.0 * Pi;

Task::Task(TypeTask typeTask, Node *start, Node *end, const QString &id, int weight, QGraphicsItem *parent, QGraphicsScene *scene)
        : QGraphicsLineItem(parent, scene)
{
    myTypeTask = typeTask;
    startNode = start;
    endNode = end;
    _id = id;
    _weight = weight;

    _state = Normal;
    _slack = "1";
}

QRectF Task::boundingRect() const
{
    qreal extra = (pen().width() + 10) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                           line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Task::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Task::updatePosition()
{
    QLineF line(mapFromItem(startNode, 0, 0), mapFromItem(endNode, 0, 0));
    setLine(line);
}

void Task::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (startNode->collidesWithItem(endNode))
        return;

    // [0]
    QColor color;
    switch(_state){
    case Normal:
        color = Qt::darkGray;
        break;
    case Aller:
        color = Qt::blue;
        break;
    case Retour:
        color = Qt::darkMagenta;
        break;
    case Fin:
        if (this->critique() == true)
            color = Qt::red;
        else
            color = Qt::darkGray;
        break;
    };

    Qt::PenStyle style = Qt::SolidLine;
    //if (this->selected) color = Qt::blue;
    if (myTypeTask == TaskFictive) style = Qt::DashLine;

    painter->setPen(QPen(color, 2, style, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(color);
    // [0]

    // [1] Lay diem moi
    QLineF centerLine(startNode->pos(), endNode->pos());
    qreal length = centerLine.length();

    qreal dx = ( 15 / length ) * centerLine.dx();
    qreal dy = ( 15 / length ) * centerLine.dy();

    QPointF newEndNode = endNode->pos();
    newEndNode.setX(newEndNode.x() - dx);
    newEndNode.setY(newEndNode.y() - dy);

    setLine(QLineF(newEndNode, startNode->pos()));
    // [1]

    // [2] draw the arrows
    double angle = ::acos(this->line().dx() / this->line().length());
    if (this->line().dy() >= 0)
        angle = TwoPi - angle;

    QPointF arrowP1 = this->line().p1() + QPointF(sin(angle + Pi / 3) * 15,
                                            cos(angle + Pi / 3) * 15);
    QPointF arrowP2 = this->line().p1() + QPointF(sin(angle + Pi - Pi / 3) * 15,
                                            cos(angle + Pi - Pi / 3) * 15);

    arrowHead.clear();
    arrowHead << this->line().p1() << arrowP1 << arrowP2;

    painter->drawLine(this->line());
    painter->drawPolygon(arrowHead);
    // [2]

    // [3] Ve text
    if (myTypeTask != TaskFictive){
        dx = centerLine.dx() / 2;
        dy = centerLine.dy() / 2;
        qreal x = startNode->pos().x() + dx; //+ 25;
        qreal y = startNode->pos().y() + dy; //+ 25;
        if (startNode->pos().y() < endNode->pos().y()) y -= 20;

        QString weight = QObject::tr("%1").arg(_weight);
        QString text = QObject::tr("%1 | %2").arg(_id, weight);
        painter->drawText(QRectF(x, y, text.length() * 10, 20), Qt::AlignCenter | Qt::AlignHCenter, text);
    }
    // [3]
}
