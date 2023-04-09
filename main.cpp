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

  std::vector<size_t> erdosRenyiA = {100, 300};
  Graph erdosRenyiGraph(ErdosRenyi, erdosRenyiA);
  erdosRenyiGraph.exportCSV_adjacencyEdges("res/erdosRenyiA.csv");

  return 0;
}
