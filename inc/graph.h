/**
 * @file graph.h
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#ifndef GRAPH_H
#define GRAPH_H


#include <eigen3/Eigen/Sparse>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


// Alias to adjacency matrix
typedef Eigen::SparseMatrix<unsigned short int> adjacency;


class Graph{
 private:

  /* Attributes */

  /// Define the adjacency Matrix
  adjacency adjacencyMatrix;

  /// Define the Graphs supported
  const std::vector<std::string> typesGraph = {
    "Square grid",
    "Triangular grid",
    "Erdos-Renyi",
    "Barabasi-albert"
  };


 public:
  /* Constructor */
  /**
   * @brief Constructor of the class Graph
   */
  template<typename attributesList>
    Graph(std::string typeGraph, attributesList arguments){
    // Check the typeGraph is in the vector
    if(std::find(this->typesGraph.begin(), this->typesGraph.end(), typeGraph) != this->typesGraph.end()){
      std::cout << "El grafo es de tipo" << typeGraph << std::endl;
    }

    // If not is so throw an error
    else{
      std::string error_message("Please check the type of Graphs supported. '");
      error_message += typeGraph;
      error_message += "' is not an aceptable option.\n";
      error_message += "File '";
      error_message += __FILE__;
      error_message += "', function '";
      error_message += __func__;
      error_message += "' and line '";
      error_message += std::to_string(__LINE__);
      error_message += "'.";


      throw std::invalid_argument(error_message);
    }
  };


  /* Destructor */
  /**
   * @brief Destructor of the class Graph
   */
  ~Graph();
};


#endif /* GRAPH_H */
