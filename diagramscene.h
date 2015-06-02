/****************************************************
* Auteur : MAN Le Viet, HO The Nhan, HUYNH Ngoc Tho
* C'est une classe hérité de la classe QGraphicsScene
*
*****************************************************/

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include "node.h"

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DiagramScene();

    void setNode(Node *node);
    void setTask(Task *task);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
};
#endif // DIAGRAMSCENE_H
