#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <fstream>
#include <queue>
#include <iostream>

using namespace GraphUtils;

namespace Bicoloring
{
  bool ReadGraph(std::shared_ptr<Graph>& graphPtr, std::fstream& fStream)
  {
    int numVertices;
    fStream >> numVertices;
    if (numVertices == 0)
      return false;

    graphPtr->nVertices = numVertices;

    int numRows;
    fStream >> numRows;
    for (int index = 0; index < numRows; index++)
    {
      int x;
      fStream >> x;

      int y;
      fStream >> y;

      InsertEdge(graphPtr, x, y, false);
    }
    return true;
  }

  void discoverVertex(int vertex, int parent, bool* red, bool* black)
  {
    if (parent == -1)
    {
      red[vertex] = true;
      return;
    }

    red[parent] ? black[vertex] = true : red[vertex] = true;
  }

  bool processEdge(int parent, int child, bool* red, bool* black)
  {
    return red[parent] != red[child] && black[parent] != black[child];
  }

  void bfs(std::shared_ptr<Graph>& graph, int root)
  {
    // Initialize discovered and processed.
    bool discovered[MAXV];
    bool processed[MAXV];
    bool red[MAXV];
    bool black[MAXV];
    for (int index = 0; index < MAXV; index++)
      red[index] = black[index] = processed[index] = discovered[index] = false;

    std::queue<int> queue;
    discovered[root] = true;
    discoverVertex(root, -1, red, black);
    queue.push(root);

    while (!queue.empty())
    {
      int vertex = queue.front();
      queue.pop();

      for (int child = 0; child < graph->degree[vertex]; child++)
      {
        if (discovered[graph->edges[vertex][child]] == false)
        {
          discovered[graph->edges[vertex][child]] = true;
          discoverVertex(graph->edges[vertex][child], vertex, red, black);
          queue.push(graph->edges[vertex][child]);
        }

        if (processed[graph->edges[vertex][child]] == false)
        {
          bool validEdge = processEdge(vertex, graph->edges[vertex][child], red, black);
          if (!validEdge)
          {
            std::cout << "NOT BICOLORABLE" << std::endl;
            return;
          }
        }
      }

      processed[vertex] = true;
    }

    std::cout << "BICOLORABLE"<<std::endl;
  }

  void bicoloring()
  {
    std::string file("E:\\data\\bicoloring.txt");
    std::fstream inStream(file, std::ios_base::in);

    while (true)
    {
      std::shared_ptr<Graph> graph = std::make_shared<Graph>();
      InitializeGraph(graph);

      bool validGraph = ReadGraph(graph, inStream);
      if (!validGraph)
      {
        inStream.close();
        return;
      }

      bfs(graph, 0);
    }

    inStream.close();
  }
}