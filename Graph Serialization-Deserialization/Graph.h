#pragma once
#define MAXV 200
#define MAXDEGREE 50

#include <memory>

namespace GraphUtils
{
  // TODO: Define valid edge array.
  typedef struct Graph {

    int edges[MAXV + 1][MAXDEGREE];
    int degree[MAXV + 1];
    int nVertices;
    int nEdges;

  } Graph;

  void InitializeGraph(std::shared_ptr<Graph>& graphPtr);
  void InsertEdge(std::shared_ptr<Graph>& graphPtr, int x, int y, bool isDirected = true);
}