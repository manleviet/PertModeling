#ifndef PTASKLIST_H
#define PTASKLIST_H

#include "ptask.h"

class PTaskList
{
public:
    PTaskList();
    void addTask(PTask* t);
    void removeTail();
    int getNumberTask(){ return numberTasks;}
    void setNumberTask(int number){ numberTasks = number;}
    QList<PTask *> getListTasks(){ return listTasks;}
    void setListTasks(QList<PTask *> list){ listTasks = list;}
    PXMLProvider getFileSource(){ return fileSource;}
    void setFileSource(const PXMLProvider &file){ fileSource = file;}
    PXMLProvider getFileResult(){ return fileResult;}
    void setFileResult(const PXMLProvider &file){ fileResult = file;}
    PXMLProvider getFileResultStep(){ return fileResultStep;}
    void setFileResultStep(const PXMLProvider &file){ fileResultStep = file;}

    bool loadProblemFromGraphXml();

private:
    int numberTasks; // nombre de taches instanciees
    QList<PTask *> listTasks; //la liste des taches
    PXMLProvider fileSource; // fichier XML contient les tasks
    PXMLProvider fileResult; // fichier XML contient les resultats
    PXMLProvider fileResultStep; // fichier XML contient les resultats en etaps
};
#endif // PTASKLIST_H
