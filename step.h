#ifndef STEP_H
#define STEP_H

#include <QString>

class Step
{
public:
    enum State {Aller, Retour};
    enum Action {Mark, Change, NoChange, Fin};

    Step(Action action, State state, QString early, QString late, QString id, QString idName);

    State state() {return _state;}
    Action action() {return _action;}
    QString earlyDate() {return _earlyDate;}
    QString lateDate() {return _lateDate;}
    QString id() {return _id;}
    QString idName() {return _idName;}

private:
    State _state;
    Action _action;
    QString _earlyDate;
    QString _lateDate;
    QString _id;
    QString _idName;
};

#endif // STEP_H
