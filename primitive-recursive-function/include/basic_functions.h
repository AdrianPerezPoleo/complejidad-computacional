/**
 * @file basic_functions.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Definition of the Zero and Succesor Primitive Recursive Functions.
 * @version 1.0
 * @date 2026-10-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

#include "primitive_recursive_function.h"

class Zero : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x) const {
    AddFunctionCall();
    return 0;
  }
};

class Successor : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x) const {
    AddFunctionCall();
    return x + 1;
  }
};

#endif