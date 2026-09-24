/**
 * @file stack.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that implements a stack sed by a pushdown automaton.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef STACK_H
#define STACK_H

#include <stack>
#include "alphabet.h"

class Stack {
 public:
  Stack(Symbol initial_symbol, const Alphabet& stack_alphabet);

  void Pop() { this->stack_.pop();}
 private:
  std::stack<Symbol> stack_;

  bool IsValid(const Symbol& initial_symbol, const Alphabet& alphabet) const;
};

#endif