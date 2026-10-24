/**
 * @file multiply.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Definition of the Multiply Primitive Recursive Function.
 * @version 1.0
 * @date 2026-10-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "primitive_recursive_function.h"
#include "basic_functions.h"
#include "add.h"

class Multiply : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x, int y) const {
    AddFunctionCall();
    if (y == 0) return Zero()(x);
    return Add()(x, operator()(x, y - 1));
  }
};

#endif