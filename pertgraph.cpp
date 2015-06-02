#include "pertgraph.h"

PertGraph::PertGraph()
{
    _nowStep = 0;
}

void PertGraph::setNode(Node *node)
{
    nodeList.append(node);
}

void PertGraph::setTask(Task *task)
{
    taskList.append(task);
}

void PertGraph::setStep(Step *newStep)
{
    stepList.append(newStep);
}

void PertGraph::nextStep()
{
    if (_nowStep == this->totalStep()) return;
    _nowStep++;
    this->update();
}

QString PertGraph::outputText()
{
    if (_nowStep == 0) return "";

    QString output = "LES ETAPES DE L'ALGORITHME PERT: \n";
    for (int i = 1; i <= _nowStep; i++)
    {
        Step *steptemp = this->stepList.at(i-1);
        QString idName = steptemp->idName();
        if (idName == "0") idName = "fictive";

        switch (steptemp->action()){
        case Step::Mark:
            if (steptemp->state() == Step::Aller)
                output = output + "STEP " + QObject::tr("%1").arg(i/2+1) + " : Calculer la date au plus tot de la tache " + idName + "\n";
            else if (steptemp->state() == Step::Retour)
                output = output + "STEP " + QObject::tr("%1").arg(i/2+1) + " : Calculer la date au plus tard de la tache " + idName + "\n";
            break;
        case Step::Change:
            if (steptemp->state() == Step::Aller)
                output = output + "La date au plus tot de cette tache est changee par une nouvelle valuer " + steptemp->earlyDate() + "\n";
            else if (steptemp->state() == Step::Retour)
                output = output + "La date au plus tard de cette tache est changee par une nouvelle valuer " + steptemp->earlyDate() + "\n";
            break;
        case Step::NoChange:
            if (steptemp->state() == Step::Aller)
                output = output + "La date au plus tot de cette tache n'est changee pas.\n";
            else if (steptemp->state() == Step::Retour)
                output = output + "La date au plus tard de cette tache n'est changee pas.\n";
            break;
        case Step::Fin:
            // marge totale
            output = output + "MARGE TOTALE : \n";
            for (int i = 0; i < taskList.length(); i++)
                if (taskList.at(i)->id() != "")
                    output = output + taskList.at(i)->id() + " -- " + taskList.at(i)->slack() + "\n";

            // duong critique
            output = output + "LE CHEMIN CRITIQUE : ";
            for (int i = 0; i < taskList.length(); i++)
                if (taskList.at(i)->critique() == true)
                    output = output + taskList.at(i)->id() + " ";
            break;
        };
    }
    return output;
}

void PertGraph::update()
{
    this->clearMark();
    if (_nowStep == 0) return;

    Step *steptemp = this->stepList.at(_nowStep - 1);
    Task *tasktemp = taskList.at(steptemp->id().toInt());
    switch (steptemp->action()){
    case Step::Mark:
        if (steptemp->state() == Step::Aller){
            tasktemp->setState(Task::Aller);
            tasktemp->start()->setState(Node::Aller);
            tasktemp->end()->setState(Node::Aller);
        } else if (steptemp->state() == Step::Retour){
            tasktemp->setState(Task::Retour);
            tasktemp->start()->setState(Node::Retour);
            tasktemp->end()->setState(Node::Retour);
        }
        break;
    case Step::Change:
        if (steptemp->state() == Step::Aller){
            tasktemp->end()->setState(Node::ChangeAller);
            tasktemp->end()->setEarlyDate(steptemp->earlyDate());
            tasktemp->end()->setLateDate(steptemp->lateDate());
            if (taskList.indexOf(tasktemp) == (taskList.length() -1)) // Xu ly len + 1
                tasktemp->end()->setLateDate(tasktemp->end()->earlyDate());
        } else if (steptemp->state() == Step::Retour){
            tasktemp->start()->setState(Node::ChangeRetour);
            tasktemp->start()->setEarlyDate(steptemp->earlyDate());
            tasktemp->start()->setLateDate(steptemp->lateDate());
        }
        break;
    case Step::NoChange:
        if (steptemp->state() == Step::Aller){
            tasktemp->end()->setState(Node::ChangeAller);
            if (taskList.indexOf(tasktemp) == (taskList.length() -1)) // Xu ly len + 1
                tasktemp->end()->setLateDate(tasktemp->end()->earlyDate());
        } else if (steptemp->state() == Step::Retour){
            tasktemp->start()->setState(Node::ChangeRetour);
        }
        break;
    case Step::Fin:
        for (int i = 0; i < taskList.length(); i++)
            taskList.at(i)->setState(Task::Fin);
        break;
    };
}

void PertGraph::clearMark()
{
    for (int i = 0; i < nodeList.length(); i++)
        nodeList.at(i)->setState(Node::Normal);
}

void PertGraph::setScriptStep(ScriptStep *step)
{
    for (int i = 0; i < nodeList.length(); i++)
    {
        nodeList.at(i)->setState(step->stateNode(i));
        nodeList.at(i)->setEarlyDate(step->earlyDate(i));
        nodeList.at(i)->setLateDate(step->lateDate(i));
    }
    for (int i = 0; i < taskList.length(); i++)
        taskList.at(i)->setState(step->stateTask(i));
}
