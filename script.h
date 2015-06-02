#ifndef SCRIPT_H
#define SCRIPT_H

#include "scriptstep.h"

class Script
{
public:
    Script();

    void setStep(ScriptStep *step);
    ScriptStep *currentStep();

    int totalStep() {return stepList.length();}
    int indexStep() {return _nowStep;}

    void firstStep();
    void previousStep();
    void nextStep();

    QString outputText();

private:
    QList<ScriptStep *> stepList;
    int _nowStep;
};

#endif // SCRIPT_H
