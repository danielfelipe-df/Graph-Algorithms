/**
 * @file graph.cpp
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#include <graph.h>


Graph::~Graph(){


}


void Graph::rectangular_grid(size_t N, size_t M){

  // Set the number of nodes
  this->nodes = N*M;


  // Loop over the last column. Create edge with below neighbour
  for(size_t i=0; i<N-1; i++)
    this->adjacencyEdges.push_back(edgeA(i*M + (M-1), (i+1)*M + (M-1), 1));

  // Loop over the last row. Create edge with right neighbour
  for(size_t j=0; j<M-1; j++)
    this->adjacencyEdges.push_back(edgeA((N-1)*M + j, (N-1)*M + (j+1), 1));

  // Loop over the rest of the grid
  for(size_t i=0; i<N-1; i++){
    for(size_t j=0; j<M-1; j++){

      // Create edges with right and below neighbour
      this->adjacencyEdges.push_back(edgeA(i*M + j, i*M + (j+1), 1));
      this->adjacencyEdges.push_back(edgeA(i*M + j, (i+1)*M + j, 1));
    }
  }


  // Resize adjacency according to number of nodes in the graph
  this->adjacencyMatrix.resize(N*M, N*M);

  // And save the edges in the adjacency matrix
  this->adjacencyMatrix.setFromTriplets(this->adjacencyEdges.begin(), this->adjacencyEdges.end());

  std::cout << this->adjacencyMatrix.rows() << " ";
  std::cout << this->adjacencyMatrix.cols() << std::endl;
}
