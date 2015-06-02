#ifndef SCRIPTSTEP_H
#define SCRIPTSTEP_H

#include "node.h"
#include "task.h"

class ScriptStep
{
public:
    ScriptStep();

    void setInfoNode(Node::State state, const QString &earlyDate, const QString &lateDate);
    void setInfoTask(Task::State state);
    void setOutputText(const QString &output);

    Node::State stateNode(int index) {return stateNodeList.at(index);}
    QString earlyDate(int index) {return earlyDateList.at(index);}
    QString lateDate(int index) {return lateDateList.at(index);}

    Task::State stateTask(int index) {return stateTaskList.at(index);}

    QString outputText() {return _outputText;}

private:
    QList<Node::State> stateNodeList;
    QStringList earlyDateList;
    QStringList lateDateList;

    QList<Task::State> stateTaskList;

    QString _outputText;
};

#endif // SCRIPTSTEP_H
