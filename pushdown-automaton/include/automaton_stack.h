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

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "alphabet.h"
#include "automaton_error.h"
#include "types.h"

namespace pda {
  
class AutomatonStack {
 public:
  AutomatonStack(Symbol initial_symbol, const Alphabet& stack_alphabet) : initial_symbol_{initial_symbol}, alphabet_{stack_alphabet} { 
    this->Push(initial_symbol); 
  }
  AutomatonStack(const AutomatonStack&) = default;

  void Push(const Symbol& symbol);
  void Push(const Symbols& symbols);

  Symbol Top() const { return this->stack_.back(); }
  void Pop() { if (!stack_.empty()) this->stack_.pop_back(); }
  bool IsEmpty() const { return this->stack_.empty(); }
  void Restart() { this->stack_.clear(); this->Push(initial_symbol_); }

  std::ostream& PrintContent(std::ostream& os) const;
 private:
  Symbol initial_symbol_;
  std::vector<Symbol> stack_;
  Alphabet alphabet_;
};

}
#endif