#include <QMatrix>
#include "ptasklist.h"

PTaskList::PTaskList()
{
    numberTasks = 0;
}

void PTaskList::addTask(PTask *t)
{
    listTasks.push_back(t);
    numberTasks ++;
}

void PTaskList::removeTail()
{
    listTasks.pop_back();
    numberTasks --;
}

bool PTaskList::loadProblemFromGraphXml()
{
    // Faire le parsing
   if(fileSource.parseFile()){
       // Duyet qua du lieu XML de tao ra _node va _edge
       QDomElement root = this->fileSource.getDocument().documentElement();
       if (root.tagName() != "graph")
           return false;

       QDomNodeList node = root.elementsByTagName("edge");
       for(uint i =0; i < node.length();i++)
       {
           QString id = node.at(i).toElement().attribute("id","");
           QString weight = node.at(i).toElement().attribute("weight","0");
           QString iStart = node.at(i).toElement().attribute("start","0");
           QString iEnd = node.at(i).toElement().attribute("end","0");
           PTask *myTask = new PTask(i, weight.toInt(), id, iStart, iEnd);
           this->addTask(myTask);
       }
       for(int i =0; i <this->listTasks.length();i++)
       {
          for(int j =0; j < this->listTasks.length();j++)
          {
              PTask* myTask = listTasks.at(i);
              if(listTasks.at(j)->getStart() == myTask->getEnd())
              {
                  listTasks.at(j)->addPredecessors(myTask);
                  myTask->addSuccessor(listTasks.at(j));
              }
          }
        }
        return true;
    }
    return false;
}
