#include "scriptstep.h"

ScriptStep::ScriptStep()
{
}

void ScriptStep::setInfoNode(Node::State state, const QString &earlyDate, const QString &lateDate)
{
    stateNodeList.append(state);
    earlyDateList.append(earlyDate);
    lateDateList.append(lateDate);
}

void ScriptStep::setInfoTask(Task::State state)
{
    stateTaskList.append(state);
}

void ScriptStep::setOutputText(const QString &output)
{
    _outputText = output;
}
