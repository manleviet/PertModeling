#include <QPainter>
#include <QGraphicsTextItem>
#include <QStyleOption>
#include "diagramscene.h"
#include "node.h"
#include "task.h"

class QObject;

Node::Node(float x, float y, const QString &id)
{
    setRect(-15, -15, 30, 30);
    myPolygon = this->polygon();
    setFlags(QGraphicsItem::ItemIsMovable);

    this->setPos(x, y);
    _id = id;
    _earlyDate = "0";
    _lateDate = "0";

    _state = Normal;
}

void Node::addTask(Task *task)
{
    tasks.append(task);
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-15 - adjust, -15 - adjust,
                  30 + 3 + adjust, 30 + 3 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-15,-15,30,30);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(rect().x() + 3, rect().y() + 3,
                         rect().width(), rect().height());

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }

    painter->setPen(QPen(Qt::black, 0));
    painter->setBrush(gradient);
    painter->drawEllipse(rect());
    painter->drawText(rect(), Qt::AlignCenter | Qt::AlignHCenter , _id);

    // Ve text plus tot va plus tard
    QString lateDate = _lateDate;
    if (lateDate == "-1") lateDate = "0";
    switch (_state){
    case Normal :
        painter->setPen(QPen(Qt::darkRed));
        painter->drawText(QRectF(-15, -35, _earlyDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, _earlyDate);
        painter->setPen(QPen(Qt::darkGreen));
        painter->drawText(QRectF(-15, 15, _lateDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, lateDate);
        break;
    case Aller:
        painter->setPen(QPen(Qt::blue));
        painter->drawText(QRectF(-15, -35, _earlyDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, _earlyDate);
        painter->setPen(QPen(Qt::darkGreen));
        painter->drawText(QRectF(-15, 15, _lateDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, lateDate);
        break;
    case Retour:
        painter->setPen(QPen(Qt::darkRed));
        painter->drawText(QRectF(-15, -35, _earlyDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, _earlyDate);
        painter->setPen(QPen(Qt::darkMagenta));
        painter->drawText(QRectF(-15, 15, _lateDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, lateDate);
        break;
    case ChangeAller:
        painter->setPen(QPen(Qt::red));
        painter->drawText(QRectF(-15, -35, _earlyDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, _earlyDate);
        painter->setPen(QPen(Qt::darkGreen));
        painter->drawText(QRectF(-15, 15, _lateDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, lateDate);
        break;
    case ChangeRetour:
        painter->setPen(QPen(Qt::darkRed));
        painter->drawText(QRectF(-15, -35, _earlyDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, _earlyDate);
        painter->setPen(QPen(Qt::red));
        painter->drawText(QRectF(-15, 15, _lateDate.length()*10, 20), Qt::AlignCenter | Qt::AlignHCenter, lateDate);
        break;
    };
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange){
        foreach (Task *task, tasks)
            task->updatePosition();
    }
    return value;
}
