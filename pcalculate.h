#ifndef PCALCULATE_H
#define PCALCULATE_H

#include "ptasklist.h"

class PCalculate{
public:
    PCalculate();
    PTaskList getListTask();
    void setListTask(PTaskList list);
    bool setDataFile(QString str);
    bool setResultFile(QString str);
    bool setResultFileStep(QString str);

    void initProblem();
    bool calculate();
    bool calculateEarlyDate(int nbExec);
    bool calculateLateDate(int nbExec);

    PXMLProvider getFileResult(){ return fileResult;}
    void setFileResult(const PXMLProvider &file){ fileResult = file;}

    PXMLProvider getFileResultStep(){ return fileResultStep;}
    void setFileResultStep(const PXMLProvider &file){ fileResultStep = file;}

    bool saveResultTask();
    bool insertResultTask(PTask* myTask);
    bool saveResultFile();

    bool insertResultTaskStep(int iStep, QString fromQTask, int id, int isChanged);
    bool insertResultTaskStep2(int iStep, QString fromQTask, int id, QString toQTask, int isChanged);
    bool saveResultFileStep();
    bool saveResultTaskStep();

private:
    PTaskList listTasks;
    QString strDataFile;
    QString strResultFile;
    QString strResultFileStep;
    PXMLProvider fileResult; // fichier XML contient les resultats
    PXMLProvider fileResultStep; // fichier XML contient les resultats en etaps
    QDomDocument docFile; // doc sauvegarder fichier
    QDomDocument docFileResult; // doc sauvegarder fichier resultat
};
#endif // PCALCULATE_H
