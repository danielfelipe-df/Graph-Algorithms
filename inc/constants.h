/**
 * @file constants.h
 * @author Daniel Felipe <danielfoc@protonmail.com>
 * @date 07/04/2023
 * @brief
 */


#ifndef CONSTANTS_H
#define CONSTANTS_H


/// Define the Graphs supported by the program
enum supportedGraph{
  RectangularGrid,
  TriangularGrid,
  ErdosRenyi,
  BarabasiAlbert
};



/**************** ALIASES *********************/


#include <eigen3/Eigen/Sparse>


/// Alias to adjacency Matrix
typedef Eigen::SparseMatrix<unsigned short int> matrixA;

/// Alias to weighted Matrix
typedef Eigen::SparseMatrix<double> matrixW;

/// Alias to adjacency Edge
typedef Eigen::Triplet<size_t> edgeA;

/// Alias to weighted Edge
typedef Eigen::Triplet<double> edgeW;


#endif /* CONSTANTS_H */
