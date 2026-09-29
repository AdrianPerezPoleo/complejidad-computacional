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
#include "../include/automaton_error.h"

/**
 * @brief Returns the transition associated to a given state an symbols.
 * 
 * @return std::pair<State, Symbol> Transition to be made.
 */
std::vector<Transition> TransitionTable::GetTransitions(State current_state, Symbol tape_symbol, Symbol stack_symbol) const {
  std::vector<Transition> possible_transitions;

  if (tape_symbol != '.') {
    TransitionAntecedent real_key{current_state, tape_symbol, stack_symbol};
    auto it = this->transition_table_.find(real_key);
    if (it != transition_table_.end()) {
      for (const auto& consequent : it->second) {
        possible_transitions.emplace_back(real_key, consequent);
      }
    }
  }

  TransitionAntecedent epsilon_key{current_state, '.', stack_symbol};
  auto it_epsilon = this->transition_table_.find(epsilon_key);
  if (it_epsilon != this->transition_table_.end()) {
    for (const auto& consequent : it_epsilon->second) {
      possible_transitions.emplace_back(epsilon_key, consequent);
    }
  }

  return possible_transitions;
}

/**
 * @brief Initializes the table with the productions given by the user.
 * 
 * @param table_data_ Data of the productions to be stored.
 */
void TransitionTable::InitializeTable(const std::vector<std::vector<std::string>>& table_data_) {
  int transition_id = 1;
  for (const auto& production_data : table_data_ ) {
    if (production_data.size() != 5 || production_data[0].empty() ||
        production_data[1].size() != 1 || production_data[2].size() != 1 ||
        production_data[3].empty() || production_data[4].empty()) {
      throw InvalidTransitionError("Transicion mal formada: se esperaban 5 campos validos.");
    }
    TransitionAntecedent antecedent{production_data[0], production_data[1].front(), production_data[2].front()};
    TransitionConsequent consequent{transition_id++, production_data[3], production_data[4]};
    this->transition_table_[antecedent].emplace_back(consequent);
  }
}

void TransitionTable::PrintTransitions() const {
  for (const auto& [antecedent, consequents] : this->transition_table_) {
    for (const auto& consequent : consequents) {
      std::cout << consequent.identifier << ": (" 
                << antecedent.current_state << ", " 
                << antecedent.current_tape_symbol << ", " 
                << antecedent.current_stack_symbol << ") -> (" 
                << consequent.next_state << ", " 
                << consequent.symbols_to_push << ")" 
                << std::endl;
    }
  }
}