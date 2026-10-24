/**
 * @file power.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Definition of the Power Primitive Recursive Function.
 * @version 1.0
 * @date 2026-10-24
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef POWER_H
#define POWER_H

#include "primitive_recursive_function.h"
#include "basic_functions.h"
#include "multiply.h"

class Power : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x, int y) const {
    AddFunctionCall();
    if (y == 0) return Successor()(Zero()(x));
    return Multiply()(x, this->operator()(x, y - 1));
  }
};

#endif