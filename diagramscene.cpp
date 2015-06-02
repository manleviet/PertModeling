#include <QGraphicsSceneMouseEvent>
#include "diagramscene.h"
#include "task.h"

DiagramScene::DiagramScene()
{
}

// Danh cho lop GraphProvider
void DiagramScene::setNode(Node *node)
{
    Node *nodetemp = new Node(node->x(), node->y(), node->id());
    nodetemp->setEarlyDate(node->earlyDate());
    nodetemp->setLateDate(node->lateDate());
    nodetemp->setState(node->state());
    addItem(nodetemp);
}

// Danh cho lop GraphProvider
void DiagramScene::setTask(Task *task)
{
    // xac dinh dinh dau va dinh cuoi
    QGraphicsItem *startItem = this->itemAt(QPointF(task->start()->x(), task->start()->y()));
    QGraphicsItem *endItem = this->itemAt(QPointF(task->end()->x(), task->end()->y()));

    Node *startNode = qgraphicsitem_cast<Node *>(startItem);
    Node *endNode = qgraphicsitem_cast<Node *>(endItem);

    // Khoi tao 1 task moi
    Task *tasktemp;
    if (task->typeTask() == Task::TaskNormal)
        tasktemp = new Task(Task::TaskNormal, startNode, endNode, task->id(), task->weight());
    else
        tasktemp = new Task(Task::TaskFictive, startNode, endNode, task->id(), task->weight());

    tasktemp->setState(task->state());
    tasktemp->setSlack(task->slack());
    tasktemp->setCritique(task->critique());

    startNode->addTask(tasktemp);
    endNode->addTask(tasktemp);
    tasktemp->setZValue(-1000.0);
    addItem(tasktemp);
    tasktemp->updatePosition();
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    update(sceneRect());
}
