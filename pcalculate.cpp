#include <QFile>
#include <QTextStream>
#include "pcalculate.h"

PCalculate::PCalculate()
{
}

PTaskList PCalculate::getListTask()
{
    return listTasks;
}

void PCalculate::setListTask(PTaskList list)
{
    listTasks = list;
}

bool PCalculate::setDataFile(QString str){
    this->strDataFile = str;
    PXMLProvider file(str);
    listTasks.setFileSource(file);
    return true;
}

bool PCalculate::setResultFile(QString str){
    this->strResultFile = str;
    PXMLProvider file(str);
    listTasks.setFileResult(file);
    return true;
}

bool PCalculate::setResultFileStep(QString str){
    this->strResultFileStep = str;
    PXMLProvider file(str);
    listTasks.setFileResultStep(file);
    return true;
}

/**
* Initiate the problem after load data from file
**/
void PCalculate::initProblem()
{
    listTasks.loadProblemFromGraphXml();
}

bool PCalculate::calculate(){
    this->initProblem();
    this->saveResultTaskStep();
    this->saveResultTask();

    return true;
}

bool PCalculate::calculateEarlyDate(int nbExec){
    QList<PTask*> file;
    PTask* t;
    PTask* s;
    QString str;
    PTask* finTask = new PTask(listTasks.getNumberTask(), str.setNum(listTasks.getNumberTask()));
    listTasks.addTask(finTask);
    for (int n=0; n<listTasks.getNumberTask() - 1; n++) {
        t = listTasks.getListTasks().at(n);
        if (t->getNumberPred()==0) { // pas de predecesseur
            file.insert(0, t);
        }
        if(t->getNumberSucc() == 0)
        {
            finTask->addPredecessors(t);
            t->addSuccessor(finTask);
        }
    }
    while(!(file.isEmpty())){
        t = file.takeFirst();
        int d = t->getCommencementDate() + t->getDurationTask();
        for (int i=0; i<t->getNumberSucc(); i++){
            int isChanged = 0;
            s = t->getListSucc().at(i);
            if (s->getCommencementDate() < d) {
                isChanged = 1;
                s->setCommencementDate(d);
                for(int j =0; j < s->getListPred().size();j++){
                    PTask* tt = s->getListPred().at(j);
                    if(tt->getEarlyDate() < d){
                        tt->setEarlyDate(d);
                    }
                }

            }
            if(i == 0)
            {
                this->insertResultTaskStep(nbExec, t->getName(),t->getIDTask(), isChanged);
                nbExec++;
            }

            s->decreaseNumberPred();
            if (s->getNumberPred() == 0) {
                file.insert(0, s);
                //file.add(0,s);
            }
        }
    }

    for (int n=0; n<listTasks.getNumberTask(); n++) {
        listTasks.getListTasks().at(n)->setNumberPred(listTasks.getListTasks().at(n)->getNumberLinkPred());
    }
    PTask* mTask = listTasks.getListTasks().at(listTasks.getNumberTask() - 1);
    for(int i = 0; i < mTask->getNumberPred();i++)
    {
        mTask->getListPred().at(i)->resetListSucc();
    }
    //listTasks.removeTail();
    int late  = finTask->getCommencementDate() + finTask->getDurationTask();
    listTasks.getListTasks().at(listTasks.getNumberTask() - 1)->setLateDate(late);
    listTasks.getListTasks().at(listTasks.getNumberTask() - 1)->setEarlyDate(late);

    return (nbExec == listTasks.getNumberTask());
}

bool PCalculate::calculateLateDate(int nbExec){
    QList<PTask *> file;
    PTask* t;
    PTask* s;
    QString str;
    PTask* finTask = new PTask(listTasks.getNumberTask(), str.setNum(listTasks.getNumberTask()));
    listTasks.addTask(finTask);
    for (int n=0; n<listTasks.getNumberTask() - 1; n++) {
        t = listTasks.getListTasks().at(n);
        if (t->getNumberSucc()==0) { // pas de successeur
            listTasks.getListTasks().at(n)->setLateDate(listTasks.getListTasks().at(n)->getEarlyDate());
            file.insert(0, t);
        }
        if(t->getNumberPred() == 0)
        {
            finTask->addSuccessor(t);
            t->addPredecessors(finTask);
        }
    }
    while(!(file.isEmpty())){
        t= file.takeFirst();
        int d = t->getLateDate() - t->getDurationTask();
        for (int i=0; i < t->getNumberPred(); i++){
            int isChanged = 0;
            s = t->getListPred().at(i);
            if (s->getLateDate() > d || s->getLateDate() == -1) {
                s->setLateDate(d);
                s->setSlack(s->getLateDate()-s->getCommencementDate()-s->getDurationTask());
                isChanged = 1;
            }
            if(i == 0)
            {
                 this->insertResultTaskStep2(nbExec, t->getName(),t->getIDTask(), s->getName(), isChanged);
                 nbExec++;
            }
            s->decreaseNumberSucc();
            if (s->getNumberSucc() == 0) {
                file.insert(0, s);
            }
        }
    }

    for (int n=0; n<listTasks.getNumberTask(); n++) {
        listTasks.getListTasks().at(n)->setNumberSucc(listTasks.getListTasks().at(n)->getNumberLinkSucc());
    }

    int index = 2;
    while(index != 0){
        PTask* mTask = listTasks.getListTasks().at(listTasks.getNumberTask() - 1);
        for(int i = 0; i < mTask->getNumberPred();i++)
        {
            mTask->getListPred().at(i)->resetListSucc();
        }

        for(int i = 0; i < mTask->getNumberSucc();i++)
        {
            mTask->getListSucc().at(i)->resetListPred();
        }

        listTasks.removeTail();
        index --;
    }

    //determiner le chemin critique
    QList<PTask *> listeTaskCritique;
    for(int i = 0; i < listTasks.getNumberTask();i++)
    {
        if(listTasks.getListTasks().at(i)->getEarlyDate() == listTasks.getListTasks().at(i)->getLateDate())
        {
            listeTaskCritique.push_back(listTasks.getListTasks().at(i));
        }
    }

    for(int i = 0; i < listeTaskCritique.length();i++)
    {
        PTask* task = listeTaskCritique.at(i);
        QString qEnd = task->getEnd();
        QString qStart = task->getStart();
        int flag1  = 0;
        int flag2 = 0;
        for(int j = 0; j < listeTaskCritique.length();j++)
        {
            QString qEnd2 = listeTaskCritique.at(j)->getEnd();
            QString qStart2 = listeTaskCritique.at(j)->getStart();
            if(qEnd == qStart2)
            {
                flag1 = 1;
            }
            if(qStart == qEnd2)
            {
                flag2 = 1;
            }
        }
        if(task->getNumberLinkPred() == 0 && flag1 == 1)
            task->setIsCritique(1);
        if(task->getNumberLinkSucc() == 0 && flag2 == 1)
            task->setIsCritique(1);
        if(flag1 == 1 && flag2 == 1)
            task->setIsCritique(1);
    }

        //listTasks.removeTail();
        //listTasks.removeTail();
        return (nbExec - 1 == listTasks.getNumberTask());
}

bool PCalculate::insertResultTaskStep(int iStep, QString fromQTask,int id, int isChanged)
 {
      // Faire le parsing
       QDomElement el = this->docFile.createElement("Step");
       el.setAttribute("step", iStep);
       el.setAttribute("idName", fromQTask);
       el.setAttribute("id", id);
       el.setAttribute("isChanged", isChanged);

       for(int i=0; i<this->getListTask().getNumberTask(); i++)
       {
           if(listTasks.getListTasks().at(i)->getName() == fromQTask)
           {
                el.setAttribute("earlyDate", listTasks.getListTasks().at(i)->getEarlyDate());
                el.setAttribute("lateDate", listTasks.getListTasks().at(i)->getLateDate());
            }
       }
       ((this->docFile.elementsByTagName("ResultPert").item(0))).appendChild(el);
       return true;
 }

bool PCalculate::insertResultTaskStep2(int iStep, QString fromQTask,int id, QString toQTask, int isChanged)
 {
      // Faire le parsing
       QDomElement el = this->docFile.createElement("Step");
       el.setAttribute("step", iStep);
       el.setAttribute("idName", fromQTask);
       el.setAttribute("id", id);
       el.setAttribute("isChanged", isChanged);

       for(int i=0; i<this->getListTask().getNumberTask(); i++)
       {
           if(listTasks.getListTasks().at(i)->getName() == toQTask)
           {
                el.setAttribute("earlyDate", listTasks.getListTasks().at(i)->getEarlyDate());
                el.setAttribute("lateDate", listTasks.getListTasks().at(i)->getLateDate());
            }
       }
       ((this->docFile.elementsByTagName("ResultPert").item(0))).appendChild(el);
       return true;
 }

bool PCalculate::saveResultTaskStep()
{
    int numStep = 0;
    QDomElement el = this->docFile.createElement("ResultPert");
    this->docFile.appendChild(el);
    this->calculateEarlyDate(numStep);
    this->calculateLateDate(numStep);
    this->saveResultFileStep();
    return true;
}

bool PCalculate::saveResultTask(){

    QDomElement el = this->docFileResult.createElement("ResultPert");
     this->docFileResult.appendChild(el);

     for(int i=0; i<listTasks.getNumberTask(); i++)
     {
         this->insertResultTask(listTasks.getListTasks().at(i));
     }

     this->saveResultFile();
     return true;
}

 /**
*Ajouter une task dans le Document
*/
bool PCalculate::insertResultTask(PTask* myTask)
{
    QDomElement el = this->docFileResult.createElement("Node");
    el.setAttribute("id", myTask->getIDTask());
    el.setAttribute("name", myTask->getName());
    el.setAttribute("earlydate", myTask->getEarlyDate());
    el.setAttribute("latedate", myTask->getLateDate());
    el.setAttribute("dateCommence", myTask->getCommencementDate());
    el.setAttribute("slack", myTask->getSlack());
    el.setAttribute("isCritique", myTask->isTacheCritique());
    ((this->docFileResult.elementsByTagName("ResultPert").item(0))).appendChild(el);
    return true;
}

bool PCalculate::saveResultFile()
{
    const int Indent = 4;
    QFile file(strResultFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }
    QTextStream out(&file);
    this->docFileResult.save(out, Indent);
    return true;
}

bool PCalculate::saveResultFileStep()
{
    const int Indent = 4;
    QFile file(this->strResultFileStep);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }
    QTextStream out(&file);
    this->docFile.save(out, Indent);
    return true;
}
