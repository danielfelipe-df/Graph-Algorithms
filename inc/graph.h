/**
 * @file graph.h
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#ifndef GRAPH_H
#define GRAPH_H


#include <constants.h>

#include <string>
#include <vector>
#include <iostream>


/**
 * @class Graph
 * @brief
 */
class Graph{
 private:

  /* Attributes */

  /// Number of nodes
  size_t numberNodes;

  /// Edges (without weight) in the graph
  std::vector<edgeA> adjacencyEdges;

  /// Edges (with weight) in the graph
  std::vector<edgeW> weightedEdges;

  /// Define the adjacency Matrix
  matrixA adjacencyMatrix;

  /// Define the weighted Matrix
  matrixW weightedMatrix;



 public:
  /* Constructor */
  /**
   * @brief Constructor of the class Graph
   */
  template<typename attributesList>
    Graph(supportedGraph graph, attributesList arguments){
    // Check the graph is supported
    switch (graph){
    case RectangularGrid:
      std::cout << "El grafo es de tipo" << graph << std::endl;
      this->rectangular_grid(arguments[0], arguments[1]);
      break;

    case TriangularGrid:
      std::cout << "El grafo es de tipo" << graph << std::endl;
      this->triangular_grid(arguments[0], arguments[1]);
      break;

    case ErdosRenyiA:
      std::cout << "El grafo es de tipo" << graph << std::endl;
      this->erdos_renyi_A(arguments[0], arguments[1]);
      break;

    case ErdosRenyiB:
      std::cout << "El grafo es de tipo" << graph << std::endl;
      this->erdos_renyi_B(arguments[0], arguments[1]);
      break;

    case BarabasiAlbert:
      std::cout << "El grafo es de tipo" << graph << std::endl;
      break;

    // If not is so throw an error
    default:
      std::string error_message("Please check the type of Graphs supported. '");
      error_message += graph;
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


  /* Getter functions */

  size_t get_numberNodes(){return this->numberNodes;};
  std::vector<edgeA> get_adjacencyEdges(){return this->adjacencyEdges;};
  std::vector<edgeW> get_weightedEdges(){return this->weightedEdges;};
  matrixA get_adjacencyMatrix(){return this->adjacencyMatrix;};
  matrixW get_weightedMatrix(){return this->weightedMatrix;};


  /* Export CSV functions */

  void exportCSV_adjacencyEdges(std::string outputname);


  /* Functions */

  /**
   * @brief Constructor of a Rectangular Grid graph of size N*M
   * @param N Number of nodes in a row
   * @param M Number of nodes in a column
   */
  void rectangular_grid(size_t N, size_t M);

  /**
   * @brief Constructor of a Triangular Grid graph of size N*M
   * @param N Number of not-overlapped centered honeycombs in a row
   * @param M Number of not-overlapped centered honeycombs in a column
   */
  void triangular_grid(size_t N, size_t M);

  /**
   * @brief Constructor of a Erdös-Renyí graph of N nodes and K edges using Algorithm A.
   * @param N Number of nodes
   * @param K Number of edges
   */
  void erdos_renyi_A(size_t N, size_t K);

  /**
   * @brief Constructor of a Erdös-Renyí graph of N nodes and K edges using Algorithm B.
   * @param N Number of nodes
   * @param p Probability an edge exists
   */
  void erdos_renyi_B(size_t N, double p);
};


#endif /* GRAPH_H */
