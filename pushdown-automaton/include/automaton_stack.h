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

using Symbols = std::string;

class AutomatonStack {
 public:
  AutomatonStack(Symbol initial_symbol, const Alphabet& stack_alphabet) : initial_symbol_{initial_symbol}, alphabet_{stack_alphabet} { 
    this->Push(initial_symbol); 
  }

  AutomatonStack(const AutomatonStack&) = default;

  void Push(Symbol symbol) {
    if (this->alphabet_.ContainsSymbol(symbol)) {
      stack_.push_back(symbol);
    } else {
      // Lanzar error de símbolo no válido.
    }
  }

  void Push(Symbols symbols) {
    std::reverse(symbols.begin(), symbols.end());
    for (const auto& symbol : symbols) {
      if (symbol == this->kEmptySymbol) break;
      this->Push(symbol);
    }
  }

  Symbol Top() const { return this->stack_.back(); }
  void Pop() { if (!stack_.empty()) this->stack_.pop_back(); }
  bool IsEmpty() const { return this->stack_.empty(); }
  void Restart() { this->stack_.clear(); this->Push(initial_symbol_); }

  std::ostream& PrintContent(std::ostream& os) const {
    std::string stack_content = "";
    for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) {
      stack_content += *it;
    }
    if (stack_content == "") stack_content = "-";
    os << stack_content;
    return os; 
  }

 private:
  Symbol initial_symbol_;
  std::vector<Symbol> stack_;
  Alphabet alphabet_;

  static constexpr Symbol kEmptySymbol = '.';
};

#endif