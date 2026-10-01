/**
 * @file transition_table.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that simulates a transition table.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TRANSITION_TABLE_H
#define TRANSITION_TABLE_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>

#include "types.h"

struct TransitionAntecedent {
  State current_state;
  Symbol current_tape_symbol;
  Symbol current_stack_symbol;

  bool operator<(const TransitionAntecedent& other) const {
    return std::tie(current_state, current_tape_symbol, current_stack_symbol) <
           std::tie(other.current_state, other.current_tape_symbol, other.current_stack_symbol);
  }
};

struct TransitionConsequent {
  int identifier;
  State next_state;
  Symbols symbols_to_push;
};

struct Transition {
  TransitionAntecedent antecedent;
  TransitionConsequent consequent;
};

class TransitionTable {
 public:
  explicit TransitionTable(const std::vector<std::vector<std::string>>& table_data_) {
    InitializeTable(table_data_);
  }

  std::vector<Transition> GetTransitions(State, Symbol, Symbol) const;
  std::vector<Transition> GetAllTransitions() const;
  void PrintTransitions() const;
 private:
  std::map<TransitionAntecedent, std::vector<TransitionConsequent>>transition_table_;

  void InitializeTable(const std::vector<std::vector<std::string>>& table_data_);
};

#endif