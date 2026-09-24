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
#include <string>
#include <algorithm>

#include "alphabet.h"

using Symbols = std::string;

class AutomatonStack {
 public:
  AutomatonStack(Symbol initial_symbol, const Alphabet& stack_alphabet) : alphabet_{stack_alphabet} { this->Push(initial_symbol); }

  void Push(Symbol symbol) {
    if (this->alphabet_.ContainsSymbol(symbol)) {
      stack_.push(symbol);
    } else {
      // Lanzar error de símbolo no válido.
    }
  }

  void Push(Symbols symbols) {
    std::reverse(symbols.begin(), symbols.end());
    for (const auto& symbol : symbols) {
      std::cout << "Introducimos " << symbol << std::endl;
      this->Push(symbol);
    }
  }

  Symbol Top() const { return this->stack_.top(); }
  void Pop() { this->stack_.pop(); }
  bool Empty() const { return this->stack_.empty(); }
 private:
  std::stack<Symbol> stack_;
  Alphabet alphabet_;
};

#endif