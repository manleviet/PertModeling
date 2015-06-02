#include <QDomDocument>
#include <QFile>
#include "graphprovider.h"
#include "pertgraph.h"
#include "step.h"
#include "scriptstep.h"

GraphProvider::GraphProvider(){}

bool GraphProvider::readGraph(PertGraph *pert, Script *script, const QString &fileName)
{
    if (fileName.isEmpty()) return false;

    QFile file(fileName);

    QString errorStr;
    int errorLine;
    int errorColumn;

    // Load file XML vao QDomDocument
    QDomDocument doc;
    if (!doc.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
        return false;

    // Duyet qua du lieu XML de tao ra _node va _edge
    QDomElement root = doc.documentElement();
    if (root.tagName() != "graph")
        return false;

    ScriptStep *step = new ScriptStep();
    QDomElement element = root.firstChildElement();
    while (!element.isNull()){
        if (element.tagName() == "node"){
            QString id = element.attribute("id","0");
            QString x = element.attribute("x","0");
            QString y = element.attribute("y","0");

            Node *nodetemp = new Node(x.toFloat(), y.toFloat(), id);
            pert->setNode(nodetemp);
            step->setInfoNode(nodetemp->state(), nodetemp->earlyDate(), nodetemp->lateDate());
        } else if (element.tagName() == "edge"){
            QString id = element.attribute("id","");
            QString weight = element.attribute("weight","0");
            QString start = element.attribute("start","0");
            QString end = element.attribute("end","0");

            Node *startNode = pert->node(start.toInt());
            Node *endNode = pert->node(end.toInt());

            Task *tasktemp;
            if (id == "")
                tasktemp = new Task(Task::TaskFictive, startNode, endNode, id, weight.toInt());
            else
                tasktemp = new Task(Task::TaskNormal, startNode, endNode, id, weight.toInt());

            pert->setTask(tasktemp);
            step->setInfoTask(tasktemp->state());
        }
        element = element.nextSiblingElement();
    }
    step->setOutputText("");
    script->setStep(step);
    return true;
}

bool GraphProvider::readResultStep(PertGraph *pert, const QString &fileName)
{
    if (fileName.isEmpty()) return false;

    QFile file(fileName);

    QString errorStr;
    int errorLine;
    int errorColumn;

    // Load file XML vao QDomDocument
    QDomDocument doc;
    if (!doc.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
        return false;

    // Duyet qua du lieu XML de tao ra _node va _edge
    QDomElement root = doc.documentElement();
    if (root.tagName() != "ResultPert")
        return false;

    QDomNodeList node = root.elementsByTagName("Step");
    // Lay day cac Aller
    int len = pert->lengthTaskList();
    for (int i = 0; i < len; i++)
    {
        QString isChanged = node.at(i).toElement().attribute("isChanged","0");
        QString earlyDate = node.at(i).toElement().attribute("earlyDate","0");
        QString lateDate = node.at(i).toElement().attribute("lateDate","0");
        QString id = node.at(i).toElement().attribute("id","0");
        QString idName = node.at(i).toElement().attribute("idName","0");

        Step *step = new Step(Step::Mark, Step::Aller, earlyDate, lateDate, id, idName);
        pert->setStep(step);
        if (isChanged == "1")
            step = new Step(Step::Change, Step::Aller, earlyDate, lateDate, id, idName);
        else if (isChanged == "0")
            step = new Step(Step::NoChange, Step::Aller, earlyDate, lateDate, id, idName);

        pert->setStep(step);
    }

    // Lay day cac Retour
    for (int i = (len + 1); i < (2 * len + 1); i++)
    {
        QString isChanged = node.at(i).toElement().attribute("isChanged","0");
        QString earlyDate = node.at(i).toElement().attribute("earlyDate","0");
        QString lateDate = node.at(i).toElement().attribute("lateDate","0");
        QString id = node.at(i).toElement().attribute("id","0");
        QString idName = node.at(i).toElement().attribute("idName","0");

        Step *step = new Step(Step::Mark, Step::Retour, earlyDate, lateDate, id, idName);
        pert->setStep(step);
        if (isChanged == "1")
            step = new Step(Step::Change, Step::Retour, earlyDate, lateDate, id, idName);
        else if (isChanged == "0")
            step = new Step(Step::NoChange, Step::Retour, earlyDate, lateDate, id, idName);
        pert->setStep(step);
    }

    Step *step = new Step(Step::Fin, Step::Retour, "0", "0", "0", "0");
    pert->setStep(step);

    return true;
}

bool GraphProvider::readResult(PertGraph *pert, const QString &fileName)
{
    if (fileName.isEmpty()) return false;

    QFile file(fileName);

    QString errorStr;
    int errorLine;
    int errorColumn;

    // Load file XML vao QDomDocument
    QDomDocument doc;
    if (!doc.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
        return false;

    // Duyet qua du lieu XML de tao ra _node va _edge
    QDomElement root = doc.documentElement();
    if (root.tagName() != "ResultPert")
        return false;

    QDomNodeList node = root.elementsByTagName("Node");
    // Lay day cac Aller
    for (uint i = 0; i < node.length(); i++)
    {
        QString id = node.at(i).toElement().attribute("id","0");
        QString slack = node.at(i).toElement().attribute("slack","0");
        QString critique = node.at(i).toElement().attribute("isCritique","0");
        bool isCritique = false;

        if (critique == "1") isCritique = true;

        pert->task(id.toInt())->setSlack(slack);
        pert->task(id.toInt())->setCritique(isCritique);
    }

    return true;
}
