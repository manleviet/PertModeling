#include "script.h"

Script::Script()
{
    _nowStep = 0;
}

void Script::setStep(ScriptStep *step)
{
    stepList.append(step);
}

ScriptStep *Script::currentStep()
{
    return stepList.at(this->indexStep());
}

void Script::firstStep()
{
    _nowStep = 0;
}

void Script::previousStep()
{
    _nowStep--;
}

void Script::nextStep()
{
    _nowStep++;
}

QString Script::outputText()
{
    return stepList.at(_nowStep)->outputText();
}
