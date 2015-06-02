#include "ptask.h"

PTask::PTask() { // constructeur
    numberPredecessors = 0;
    numberSuccessors = 0;
    numberLinkPredecessors = 0;
    numberLinkSuccessors = 0;
    durationTask = 0;
    lateDate = -1;
    commencementDate = 0;
    earlyDate = 0;//durationTask;
    idTask = 0;
    nameTask = "";
    isCritique = 0;
    start = end = "";
}

PTask::PTask(QString name) { // constructeur
    numberPredecessors = 0;
    numberSuccessors = 0;
    numberLinkPredecessors = 0;
    numberLinkSuccessors = 0;
    durationTask = 0;
    lateDate = -1;
    commencementDate = 0;
    earlyDate = 0;//durationTask;
    idTask = 0;
    nameTask = name;
    slack = 0;
    isCritique = 0;
    start = end = "";
}

PTask::PTask(int id, int d, QString name) { // constructeur
    numberPredecessors = 0;
    numberSuccessors = 0;
    numberLinkPredecessors = 0;
    numberLinkSuccessors = 0;
    durationTask = d;
    lateDate = -1;
    commencementDate = 0;
    earlyDate = 0;//durationTask;
    idTask = id;
    nameTask = name;
    slack = 0;
    isCritique = 0;
    start = end = "";
}

PTask::PTask(int id, int d, QString name, QString istart, QString iend)
{
    numberPredecessors = 0;
    numberSuccessors = 0;
    numberLinkPredecessors = 0;
    numberLinkSuccessors = 0;
    durationTask = d;
    lateDate = -1;
    commencementDate = 0;
    earlyDate = 0;//durationTask;
    idTask = id;
    nameTask = name;
    slack = 0;
    isCritique = 0;
    this->start = istart;
    this->end = iend;
}

PTask::PTask(int id, QString name) { // constructeur
    numberPredecessors = 0;
    numberSuccessors = 0;
    numberLinkPredecessors = 0;
    numberLinkSuccessors = 0;
    durationTask = 0;
    lateDate = -1;
    commencementDate = 0;
    earlyDate = 0;//durationTask;
    idTask = id;
    nameTask = name;
    slack = 0;
    isCritique = 0;
    start = end = "";
}

void PTask::addSuccessor(PTask* t) { // ajoute la tache t a la liste des successeurs
    listSuccessors.insert(0, t);
    numberSuccessors++;
    numberLinkSuccessors ++;
}

void PTask::addPredecessors(PTask* t) { // ajoute la tache t a la liste des predecessors
    listPredecessors.insert(0,t);
    numberPredecessors++;
    numberLinkPredecessors ++;
}

QList<PTask *> PTask::getListSucc(){
    return listSuccessors;
}

QList<PTask *> PTask::getListPred(){
    return listPredecessors;
}

void PTask::resetListSucc(){
    this->listSuccessors.clear();
    numberSuccessors =0;
    numberLinkSuccessors =0;
}

void PTask::resetListPred(){
    numberPredecessors=0;
    numberLinkPredecessors =0;
}
