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

  std::vector<int> vec = {0, 1, 2, 3, 4, 5};
  Graph squareGrid2(TriangularGrid, vec);

  // Graph other(FuckYou, 78);

  return 0;
}
