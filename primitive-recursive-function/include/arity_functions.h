/**
 * @file arity_functions.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Definition of the Primitive Recurisve Functions based on their arity.
 * @version 1.0
 * @date 26-10-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ARITY_FUNCTIONS_H
#define ARITY_FUNCTIONS_H

#include "primitive_recursive_function.h"
#include "primitive_recursive_function_error.h"

class UnaryPrimitiveFunction : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x) const { return evaluate(x); }

  int operator()(const std::vector<int>& operands) const override final {
    if (operands.size() != 1) throw WrongArity("Se esperaba 1 argumento.");
    return evaluate(operands[0]);
  }
 protected:
  virtual int evaluate(int x) const = 0;
};

class BinaryPrimitiveFunction : public PrimitiveRecursiveFunction {
 public:
  int operator()(int x, int y) const { return evaluate(x, y); }

  int operator()(const std::vector<int>& operands) const override final {
    if (operands.size() != 2) throw WrongArity("Se esperaban 2 argumentos.");
    return evaluate(operands[0], operands[1]);
  }
 protected:
  virtual int evaluate(int x, int y) const = 0;
};

#endif