/**
 * @file add.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Definition of the Add Primitive Recursive Function.
 * @version 1.0
 * @date 2026-10-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ADD_H
#define ADD_H

#include "primitive_recursive_function.h"
#include "basic_functions.h"

class Add : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x, int y) const {
    AddFunctionCall();
    if (y == 0) return x;
    return Successor()(this->operator()(x, y - 1));
  }
};

#endif