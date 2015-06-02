#include "step.h"

Step::Step(Action action, State state, QString early, QString late, QString id, QString idName)
{
    _action = action;
    _state = state;
    _earlyDate = early;
    _lateDate = late;
    _id = id;
    _idName = idName;
}
