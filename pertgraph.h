#ifndef PERTGRAPH_H
#define PERTGRAPH_H

#include "node.h"
#include "task.h"
#include "step.h"
#include "scriptstep.h"

class PertGraph
{
public:
    PertGraph();

    int lengthNodeList() {return nodeList.length();}
    void setNode(Node *node);
    Node *node(int i) {return nodeList.at(i);}
    int lengthTaskList() {return taskList.length();}
    void setTask(Task *task);
    Task* task(int i) {return taskList.at(i);}

    void setStep(Step *newStep);
    int totalStep() {return stepList.length();}
    void nextStep();

    QString outputText();

    void setScriptStep(ScriptStep *step);

private:
    void update();
    void clearMark();

    QList<Node *> nodeList;
    QList<Task *> taskList;
    QList<Step *> stepList;
    int _nowStep;
};
#endif // PERTGRAPH_H
