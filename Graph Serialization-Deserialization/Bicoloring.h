#pragma once
#include <memory>
#include "Graph.h"

namespace Bicoloring
{
  bool ReadGraph(std::shared_ptr<GraphUtils::Graph>& graphPtr, std::fstream& fStream);
  void discoverVertex(int vertex, int parent, bool* red, bool* black);
  bool processEdge(int parent, int child, bool* red, bool* black);
  void bfs(std::shared_ptr<GraphUtils::Graph>& graph, int root);
  void bicoloring();
}