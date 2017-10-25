#include "stdafx.h"
#include "Graph.h"

namespace GraphUtils
{
  void InitializeGraph(std::shared_ptr<Graph>& graphPtr)
  {
    for (int index = 0; index <= MAXV; index++)
      graphPtr->degree[index] = 0;

    graphPtr->nVertices = 0;
    graphPtr->nEdges = 0;
  }

  void InsertEdge(std::shared_ptr<Graph>& graphPtr, int x, int y, bool isDirected)
  {
    graphPtr->edges[x][graphPtr->degree[x]] = y;
    graphPtr->degree[x] ++;

    if (!isDirected)
      InsertEdge(graphPtr, y, x);
    else
      graphPtr->nEdges++;
  }
}