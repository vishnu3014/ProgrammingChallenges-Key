// Graph Serialization-Deserialization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include <string>

#define MAXV 50
#define MAXDEGREE 50

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

int main()
{
  std::shared_ptr<Graph> graphPtr = std::make_shared<Graph>();
  InitializeGraph(graphPtr);
  bool isDirected = false;

  int numRows;
  std::string file("E:\\Data\\data-1.txt");
  ReadGraph(graphPtr, numRows, file, isDirected);

  std::fstream outStream("E:\\Data\\outData.txt", std::ios_base::out);
  WriteGraph(graphPtr, outStream, isDirected);
  outStream.close();

  return 0;
}

