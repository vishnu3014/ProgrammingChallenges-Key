// Graph Serialization-Deserialization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include <string>
#include <queue>
#include <iostream>
#include <stack>
#include "Bicoloring.h"
#include "PlayingWheels.h"

#define MAXV 50
#define MAXDEGREE 50

// TODO: Define valid edge array.
typedef struct Graph {

  int edges[MAXV + 1][MAXDEGREE];
  int degree[MAXV + 1];
  int nVertices;
  int nEdges;

} Graph;

void InitializeGraph(std::shared_ptr<Graph>& graphPtr)
{
  for (int index = 0; index <= MAXV; index++)
    graphPtr->degree[index] = 0;

  graphPtr->nVertices = 0;
  graphPtr->nEdges = 0;
}

void InsertEdge(std::shared_ptr<Graph>& graphPtr, int x, int y, bool isDirected = true)
{
  graphPtr->edges[x][graphPtr->degree[x]] = y;
  graphPtr->degree[x] ++;

  if (!isDirected)
    InsertEdge(graphPtr, y, x);
  else
    graphPtr->nEdges++;
}

void ReadGraph(std::shared_ptr<Graph>& graphPtr, int& numRows, std::string file, bool directed)
{
  std::fstream inStream(file, std::ios_base::in);

  inStream >> graphPtr->nVertices;
  inStream >> numRows;

  for (int index = 0; index < numRows; index++)
  {
    int x;
    inStream >> x;

    int y;
    inStream >> y;

    InsertEdge(graphPtr, x, y, directed);
  }

  inStream.close();
}

// The output is a directed graph. TODO: Can we make this undirected graph ?
void WriteGraph(std::shared_ptr<Graph>& graphPtr, std::fstream& outStream, bool isDirected)
{
  outStream << graphPtr->nVertices << " " << graphPtr->nEdges << "\n";

  for (int index = 0; index < graphPtr->nVertices; index++)
    for (int inIndex = 0; inIndex < graphPtr->degree[index]; inIndex++)
    {
      if (graphPtr->edges[index][inIndex] == -1)
        continue;

      outStream << index << " " << graphPtr->edges[index][inIndex] << "\n";

      if (isDirected)
        continue;

      int toVertex = graphPtr->edges[index][inIndex];
      for (int toVertexIndex = 0; toVertexIndex < graphPtr->degree[toVertex]; toVertexIndex++)
        if (graphPtr->edges[toVertex][toVertexIndex] == index)
        {
          graphPtr->edges[toVertex][toVertexIndex] = -1;
          break;
        }
    }
}

void discoverVertex(int vertex)
{
  // When the vertex is discovered
}

void processVertex(int vertex)
{
  std::cout << "Vertex: ";
  std::cout << vertex << std::endl;
  // When the vertex is processed.
}

void processEdge(int fromV, int toV)
{
  // When the edge is processed.
}

void initializeSearch(bool discovered[MAXV], bool processed[MAXV], int parent[MAXV])
{
  for (int index = 0; index < MAXV; index++)
  {
    discovered[index] = processed[index] = false;
    parent[index] = -1;
  }
}

void bfs(std::shared_ptr<Graph>& graph, int root)
{
  std::queue<int> queue;
  bool discovered[MAXV];
  bool processed[MAXV];
  int parent[MAXV];

  initializeSearch(discovered, processed, parent);

  queue.push(root);
  discoverVertex(root);
  discovered[root] = true;

  while (!queue.empty())
  {
    int vertex = queue.front();
    queue.pop();

    for (int index = 0; index < graph->degree[vertex]; index++)
    {
      if (discovered[graph->edges[vertex][index]] == false)
      {
        discoverVertex(graph->edges[vertex][index]);
        discovered[graph->edges[vertex][index]] = true;

        parent[graph->edges[vertex][index]] = vertex;
        queue.push(graph->edges[vertex][index]);
      }

      // Discoverted is always true at this point
      if (processed[graph->edges[vertex][index]] == false)
        processEdge(vertex, index);
    }

    processed[vertex] = true;
    processVertex(vertex);
  }
}

void dfs(std::shared_ptr<Graph>& graph, int root)
{
	std::stack<int> stack;
	bool discovered[MAXV];
	bool processed[MAXV];
	int parent[MAXV];

	initializeSearch(discovered, processed, parent);
  
  stack.push(root);
  discovered[root] = true;
  discoverVertex(root);

  while (!stack.empty())
  {
    int vertex = stack.top();
    stack.pop();

    for (int index = 0; index < graph->degree[vertex]; index++)
    {
      if (discovered[graph->edges[vertex][index]] == false)
      {
        discovered[graph->edges[vertex][index]] == true;
        discoverVertex(graph->edges[vertex][index]);

        stack.push(graph->edges[vertex][index]);
        parent[graph->edges[vertex][index]] = vertex;
      }

      if (processed[graph->edges[vertex][index]] == false)
        processEdge(vertex, index);
    }

    processed[vertex] = true;
    processVertex(vertex);
  }
}

int main()
{
  //std::shared_ptr<Graph> graphPtr = std::make_shared<Graph>();
  //InitializeGraph(graphPtr);
  //bool isDirected = false;

  //int numRows;
  //std::string file("E:\\Data\\data-1.txt");
  //ReadGraph(graphPtr, numRows, file, isDirected);

  ///*
  //std::fstream outStream("E:\\Data\\outData.txt", std::ios_base::out);
  //WriteGraph(graphPtr, outStream, isDirected);
  //outStream.close();
  //*/

  //int root = 0;
  //bfs(graphPtr, root);

  //int dummy;
  //std::cin >> dummy;


  // Bicoloring
  //Bicoloring::bicoloring();

  // PlayingWheel
  PlayingWheels::PlayingWheel();

  int dummy;
  std::cin >> dummy;

  return 0;
}
