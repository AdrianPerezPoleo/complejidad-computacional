/**
 * @file transition_table.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the TransitionTable class methods.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/transition_table.h"

/**
 * @brief Returns the transition associated to a given state an symbols.
 * 
 * @return std::pair<State, Symbol> Transition to be made.
 */
std::pair<State, Symbols> TransitionTable::GetTransition(State current_state, Symbol tape_symbol, Symbol stack_symbol) const {
  std::tuple<State, Symbol, Symbol> search_index = {current_state, tape_symbol, stack_symbol};
  try {
    return this->transition_table_.at(search_index);
  } catch (std::exception&) {
    // Imprimir el error
  }
}

void TransitionTable::PrintTransitions() const {
  for (const auto& [antecedent, consequent] : this->transition_table_) {
    std::cout << "(" << std::get<0>(antecedent) << ", "
              << std::get<1>(antecedent) << ", "
              << std::get<2>(antecedent) << ") -> ("
              << consequent.first << ", " << consequent.second << ")"
              << std::endl;
  }
}

/**
 * @brief Initializes the table with the productions given by the user.
 * 
 * @param table_data_ Data of the productions to be stored.
 */
void TransitionTable::InitializeTable(const std::vector<std::vector<std::string>>& table_data_) {
  for (const auto& production_data : table_data_ ) {
    // Revisar que el tamaño es correcto (5) o mejorar esa estructura de datos
    std::tuple<State, Symbol, Symbol> antecedent{production_data[2], production_data[3].front(), production_data[4].front()};
    std::pair<State, Symbols> consequent{production_data[0], production_data[1]};
    this->transition_table_.emplace(antecedent, consequent);
  }
}

