#ifndef GRAPHPROVIDER_H
#define GRAPHPROVIDER_H

#include "pertgraph.h"
#include "script.h"

class GraphProvider
{
public:
    GraphProvider();

    bool readGraph(PertGraph *pert, Script *script, const QString &fileName);
    bool readResultStep(PertGraph *pert, const QString &fileName);
    bool readResult(PertGraph *pert, const QString &fileName);
};
#endif // GRAPHPROVIDER_H
