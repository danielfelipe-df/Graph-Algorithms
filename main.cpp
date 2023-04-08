/**
 * @file main.cpp
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#include <graph.h>


int main(void)
{
  Graph squareGrid("Square grid", 5);

  std::vector<int> vec = {0, 1, 2, 3, 4, 5};
  Graph squareGrid2("Triangular grid", vec);

  Graph other("Fuck you", 78);

  return 0;
}
