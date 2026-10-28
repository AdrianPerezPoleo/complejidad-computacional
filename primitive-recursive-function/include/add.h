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

#include "arity_functions.h"
#include "basic_functions.h"

class Add : public BinaryPrimitiveFunction {
 public:
  int evaluate(int x, int y) const override {
    AddFunctionCall();
    if (y == 0) return Projection(1, 1)({x});

    std::vector<int> parameters = {x, y, this->operator()(x, y - 1)};
    return Successor()(Projection(3, 3)(parameters));
  }
};

#endif