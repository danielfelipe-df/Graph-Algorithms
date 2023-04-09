/**
 * @file graph.cpp
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#include <graph.h>

#include <fstream>

Graph::~Graph(){

  // Empty vectors
  adjacencyEdges.clear();
  weightedEdges.clear();
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


  // Resize adjacency according to number of nodes in the graph
  this->adjacencyMatrix.resize(this->numberNodes, this->numberNodes);

  // And save the edges in the adjacency matrix
  this->adjacencyMatrix.setFromTriplets(this->adjacencyEdges.begin(), this->adjacencyEdges.end());

  std::cout << this->adjacencyMatrix.rows() << " ";
  std::cout << this->adjacencyMatrix.cols() << std::endl;
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
