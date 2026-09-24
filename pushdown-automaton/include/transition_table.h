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
#include <tuple>
#include <utility>
#include <vector>

using Symbol = char;
using Symbols = std::string;
using State = std::string;

class TransitionTable {
 public:
  TransitionTable(const std::vector<std::vector<std::string>>& table_data_) { InitializeTable(table_data_); }

  std::pair<State, Symbols> GetTransition(State, Symbol, Symbol) const;
  void PrintTransitions() const;
 private:
  std::map<std::tuple<State, Symbol, Symbol>, std::pair<State, Symbols>> transition_table_;

  void InitializeTable(const std::vector<std::vector<std::string>>& table_data_);
};

#endif