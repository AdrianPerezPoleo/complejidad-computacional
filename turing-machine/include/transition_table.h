/**
 * @file transition_table.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2026-10-16
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TRANSITION_TABLE_H
#define TRANSITION_TABLE_H

#include "types.h"
#include "tape.h"

#include <vector>
#include <tuple>
#include <map>

namespace turing {

struct TransitionAntecedent {
  State previous_state;
  Symbols tape_symbols;

  bool operator<(const TransitionAntecedent& other) const {
    return std::tie(previous_state, tape_symbols) < 
           std::tie(other.previous_state, other.tape_symbols);
  }
};

struct TransitionConsequent {
  int id;
  State next_state;
  std::vector<Movement> movements;
};

struct Transition {
  TransitionAntecedent antecedent;
  TransitionConsequent consequent;
};

class TransitionTable {
 public:
  TransitionTable(int number_of_tapes, const std::vector<std::vector<std::string>>& table_data) {
    InitializeTable(number_of_tapes, table_data);
  }

  Transition GetTransition(const State& current_state, const Symbols& tape_symbols) const;
  void Print(std::ostream& os = std::cout) const;

  friend std::ostream& operator<<(std::ostream& os, const TransitionTable& table) {
    table.Print(os);
    return os;
  }
 private:
  int number_of_tapes_;
  std::map<TransitionAntecedent, TransitionConsequent> transition_table_;

  void InitializeTable(int, const std::vector<std::vector<std::string>>&);
  TapeMovement ConvertStringToMovement(const std::string&) const;
};

}

#endif