/**
 * @file main.cpp
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#include <graph.h>


int main(void)
{

  std::vector<size_t> sizes = {10, 10};
  Graph rectangularGrid(RectangularGrid, sizes);
  rectangularGrid.exportCSV_adjacencyEdges("res/rectangularGrid.csv");

  std::vector<size_t> vec = {2, 3};
  Graph triangularGrid(TriangularGrid, vec);
  triangularGrid.exportCSV_adjacencyEdges("res/triangularGrid.csv");

  std::vector<size_t> erdosRenyiA = {100, 396};
  Graph erdosRenyiGraphA(ErdosRenyiA, erdosRenyiA);
  erdosRenyiGraphA.exportCSV_adjacencyEdges("res/erdosRenyiA.csv");

  std::vector<float> erdosRenyiB = {100, 0.08};
  Graph erdosRenyiGraphB(ErdosRenyiB, erdosRenyiB);
  erdosRenyiGraphB.exportCSV_adjacencyEdges("res/erdosRenyiB.csv");

  return 0;
}
