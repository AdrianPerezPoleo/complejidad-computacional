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

#include <cstdarg>
#include <stdexcept>

#include "arity_functions.h"

class Zero : public UnaryPrimitiveFunction {
 public:
  int evaluate(int x) const override {
    AddFunctionCall();
    return 0;
  }
};

class Successor : public UnaryPrimitiveFunction {
 public:
  int evaluate(int x) const override {
    AddFunctionCall();
    return x + 1;
  }
};

class Projection : public PrimitiveRecursiveFunction {
 public:
  Projection(int i, int n) : i_(i), n_(n) {
    if (i_ < 1 || i_ > n_) throw PrimitiveRecursiveFunctionError("Indice de proyeccion invalido.");
  }

  int operator()(const std::vector<int>& operands) const override final {
    AddFunctionCall();
    if (operands.size() != n_) {
      throw WrongArity("La proyeccion P_" + std::to_string(i_) + "^" + std::to_string(n_) + 
                       " esperaba " + std::to_string(n_) + " argumentos.");
    }
    return operands[i_ - 1]; 
  }

 private:
  int n_;
  int i_;
};

#endif