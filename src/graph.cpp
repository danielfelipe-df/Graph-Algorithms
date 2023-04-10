/**
 * @file graph.cpp
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#include <graph.h>

#include <fstream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_01.hpp>
#include <algorithm>
#include <math.h>


Graph::~Graph(){

  // Empty vectors
  adjacencyEdges.clear();
  std::vector<edgeA>().swap(adjacencyEdges);
  weightedEdges.clear();
  std::vector<edgeW>().swap(weightedEdges);
}


void Graph::exportCSV_adjacencyEdges(std::string outputname){

  // Create an output filestream object
  std::ofstream myFile(outputname);

  myFile << "Source,Target\n";

  for(size_t i=0; i!=this->adjacencyEdges.size(); i++){
    myFile << this->adjacencyEdges[i].row();
    myFile << ",";
    myFile << this->adjacencyEdges[i].col();
    myFile << "\n";
  }

  myFile.close();
}


void Graph::rectangular_grid(size_t N, size_t M){

  // Set the number of nodes
  this->numberNodes = N*M;


  // Loop over the last column. Create edge with below neighbour
  for(size_t i=0; i!=N-1; i++)
    this->adjacencyEdges.push_back(edgeA(i*M + (M-1), (i+1)*M + (M-1), 1));

  // Loop over the last row. Create edge with right neighbour
  for(size_t j=0; j!=M-1; j++)
    this->adjacencyEdges.push_back(edgeA((N-1)*M + j, (N-1)*M + (j+1), 1));

  // Loop over the rest of the grid
  for(size_t i=0; i!=N-1; i++){
    for(size_t j=0; j!=M-1; j++){

      // Create edges with right and below neighbour
      this->adjacencyEdges.push_back(edgeA(i*M + j, i*M + (j+1), 1));
      this->adjacencyEdges.push_back(edgeA(i*M + j, (i+1)*M + j, 1));
    }
  }
}


void Graph::triangular_grid(size_t N, size_t M){

  // The regularity of HoneyCombs is given by 2*M+1.
  // This is the distance between different centers (overlapped HoneyCombs) in same column.
  size_t graphRegularity = 2*M + 1;

  // Set the number of nodes
  this->numberNodes = (2*N)*graphRegularity + M;

  // Auxiliar variables for centered HoneyComb
  size_t centerPosition, upLeftPosition;


  // Loop over the centers of over-lapped (in columns) HoneyCombs
  // Number of over-lapped (in columns) HoneyCombs comes from N rows plus N-1 intersections. So N + (N-1) = 2N-1
  for(size_t i=0; i!=(2*N-1); i++){

    // This loop is over not-overlapped (in a row) HoneyCombs
    for(size_t j=0; j!=M; j++){

      // Locate the center (overlapped HoneyComb) position and its neighbour in the up-left corner
      centerPosition = (i+1)*graphRegularity + j;
      upLeftPosition = i*graphRegularity + M + j;

      // Edge between Center and Up-Center corner
      this->adjacencyEdges.push_back(edgeA(centerPosition, centerPosition - graphRegularity, 1));

      // Edge between Center and Up-Left corner
      this->adjacencyEdges.push_back(edgeA(centerPosition, upLeftPosition, 1));

      // Edge between Center and Up-Right corner
      this->adjacencyEdges.push_back(edgeA(centerPosition, upLeftPosition + 1, 1));

      // Edge between Center and Down-Left corner
      this->adjacencyEdges.push_back(edgeA(centerPosition, upLeftPosition + graphRegularity, 1));

      // Edge between Center and Down-Right corner
      this->adjacencyEdges.push_back(edgeA(centerPosition, upLeftPosition + graphRegularity + 1, 1));

      // Edge between Up-Left corner and Down-Left corner
      this->adjacencyEdges.push_back(edgeA(upLeftPosition, upLeftPosition + graphRegularity, 1));
    }
  }


  // Loop to connect the top and bootom zone of the graph
  // The loop is over each column
  for(size_t j=0; j!=M; j++){

    // Top Zone/region of the graph
    // Edge between Center and Down-Left corner
    this->adjacencyEdges.push_back(edgeA(j, M + j, 1));

    // Edge between Center and Down-Right corner
    this->adjacencyEdges.push_back(edgeA(j, M + j + 1, 1));


    // Bottom Zone/region of the graph
    centerPosition = (2*N)*graphRegularity + j;
    upLeftPosition = (2*N-1)*graphRegularity + M + j;

    // Edge between Center and Up-Center corner
    this->adjacencyEdges.push_back(edgeA(centerPosition, centerPosition - graphRegularity, 1));

    // Edge between Center and Up-Left corner
    this->adjacencyEdges.push_back(edgeA(centerPosition, upLeftPosition, 1));

    // Edge between Center and Up-Right corner
    this->adjacencyEdges.push_back(edgeA(centerPosition, upLeftPosition + 1, 1));
  }


  // Loop to connect the right line of the graph
  for(size_t i=0; i!=(2*N-1); i++){

    // Locate the Up-Left corner (overlapped HoneyComb) position for virtual right extreme honeycomb
    upLeftPosition = (2*M) + i*graphRegularity;

    // Edge between Up-Left and Down-Left corner
    this->adjacencyEdges.push_back(edgeA(upLeftPosition, upLeftPosition + graphRegularity, 1));
  }
}


void Graph::erdos_renyi_A(size_t N, size_t K){

  // Throw error for unappropiate number of edges
  if(K > (N*(N-1)/2))
    throw std::invalid_argument("Número de vínculos demasiado grande para los nodos dados. erdos_renyi_A");

  // Number of nodes is given in the argument
  this->numberNodes = N;

  // Reserve the number of edges to be stored
  this->adjacencyEdges.reserve(K);

  // Auxiliar variable to know edges position
  std::vector<size_t> edgesPosition(K);
  size_t i, j, k;

  // Random number generator
  boost::random::mt19937 generator;
  boost::random::uniform_int_distribution<> edgesGenerator(0, N-1);

  // Loop ends when all edges are find
  while(adjacencyEdges.size() != K){

    // Get the random edge
    i = edgesGenerator(generator);
    j = edgesGenerator(generator);

    // Bacause the algorithm, only are accepted edges with i > j
    if(i > j){

      // Convert the edge from 2D (i, j) to 1D (k)
      k = j + i*(i-1)/2;

      // If the edge have not been saved, save it!
      if(std::find(edgesPosition.begin(), edgesPosition.end(), k) == edgesPosition.end()){
	edgesPosition.push_back(k);
	this->adjacencyEdges.push_back(edgeA(i, j, 1));
      }
    }
  }

  // Clear auxiliar vector
  edgesPosition.clear();
  std::vector<size_t>().swap(edgesPosition);
}


void Graph::erdos_renyi_B(size_t N, double p){

// Throw error for unappropiate value of p
  if((p < 0) and (p > 1))
    throw std::invalid_argument("Recuerde que la probabilidad de vinculacion p es entre 0 y 1. erdos_renyi_B");

  // Number of nodes is given in the argument
  this->numberNodes = N;

  // Auxiliar variable to know edges position
  size_t i, j, maxNumberEdges;

  // Calculate the maximum number of edges
  maxNumberEdges = (N+1)*(N-2)/2;

  // Random number generator
  boost::random::mt19937 generator;
  boost::random::uniform_01<> randomVariable;

  // Loop ends when all edges have been checked
  for(size_t k=0; k<maxNumberEdges; k++){

    // If the random number is less than connection probability, connect them!
    if(randomVariable(generator) < p){

      // Get the nodes of the edge
      i = std::ceil(0.5*(std::sqrt(1.0 + 8.0*(k+1)) - 1.0));
      j = k - i*(i-1)/2;

      // Save the edge
      this->adjacencyEdges.push_back(edgeA(i, j, 1));
    }
  }
}
