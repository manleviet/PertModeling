#ifndef PTASK_H
#define PTASK_H

#include <QList>
#include "pxmlprovider.h"

class PTask
{
public:
    PTask();
    PTask(QString name);
    PTask(int id, QString name);
    PTask(int id, int d, QString name);

    QString getName() {return nameTask;}
    void setName(QString name) {nameTask = name;}

    int getIDTask(){ return idTask;}
    void setIDTask(int ID){ idTask = ID;}

    void setCommencementDate(int d) {commencementDate = d;}
    int getCommencementDate(){return commencementDate;}

    void setEarlyDate(int d) {earlyDate = d;}
    int getEarlyDate(){return earlyDate;}

    void setLateDate(int d) {lateDate = d;}
    int getLateDate(){return lateDate;}

    int getDurationTask(){return durationTask;}

    int getSlack() {return slack;}
    void setSlack(int slk) {slack = slk;}

    void increaseNumberPred (){ numberPredecessors++;}
    void decreaseNumberPred (){ numberPredecessors--;}

    void increaseNumberSucc (){ numberSuccessors++;}
    void decreaseNumberSucc (){ numberSuccessors--;}

    int getNumberPred() {return numberPredecessors;}
    void setNumberPred(int num) {numberPredecessors = num;}

    int getNumberSucc() {return numberSuccessors;}
    void setNumberSucc(int num) {numberSuccessors = num;}

    int getNumberLinkPred() {return numberLinkPredecessors;}
    void setNumberLinkPred(int num) {numberLinkPredecessors = num;}

    int getNumberLinkSucc() {return numberLinkSuccessors;}
    void setNumberLinkSucc(int num) {numberLinkSuccessors = num;}

    int isTacheCritique(){return isCritique;}
    void setIsCritique(int bl){isCritique = bl;}
    QString getStart(){return start;}
    QString getEnd(){return end;}

    PTask(int id, int d, QString name, QString start, QString end);

    void addSuccessor(PTask *t); // ajoute la tache t a la liste des successeurs
    void addPredecessors(PTask *t); // ajoute la tache t a la liste des predecessors

    QList<PTask *> getListSucc();
    QList<PTask *> getListPred();

    void resetListSucc();
    void resetListPred();

private:
    int idTask; // id d'une Tache
    QList<PTask *> listSuccessors ; // la liste des successeurs
    QList<PTask *> listPredecessors ; // la liste des predecesseurs
    QString nameTask; // identifiant de la tache
    int durationTask, commencementDate, earlyDate, lateDate; // duree et date au plus tot
                                                             //date plus tard
    int slack; //marge libre
    int numberPredecessors, numberLinkPredecessors; // nombre de predecesseurs
    int numberSuccessors, numberLinkSuccessors; // nombre de successeurs
    int isCritique;
    QString start; QString end;
};
#endif // PTASK_H
