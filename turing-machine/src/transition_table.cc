/**
 * @file transition_table.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the transition table.
 * @version 1.0
 * @date 2026-10-16
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/transition_table.h"

namespace turing {

/**
 * @brief Returns the transition that corresponds to the given current state.
 * 
 * @param current_state State where the Turing machine is after obtaining the transition.
 * @param tape_symbols Symbols pointed by the tape heads.
 * @return Transition 
 */
Transition TransitionTable::GetTransition(const State& current_state, const Symbols& tape_symbols) const {
  if (transition_table_.contains({current_state, tape_symbols})) {
    auto consequent = transition_table_.at({current_state, tape_symbols});
    return {{current_state, tape_symbols}, consequent};
  } 
  throw std::out_of_range("Error: No existe una transicion definida para el estado y simbolos dados.");
}

/**
 * @brief Stores the information ot eh input file into the Transition table.
 * 
 * @param number_of_tapes 
 * @param table_data_ 
 */
void TransitionTable::InitializeTable(int number_of_tapes, const std::vector<std::vector<std::string>>& table_data_) {
  int transition_id = 1;
  for (const auto& production_data : table_data_ ) {
    for (int i{0}; i < 2 + number_of_tapes + 2 * number_of_tapes; ++i) {
      if (production_data[i].empty()) {
        throw InvalidTransitionError("Transicion mal formada: se esperaban " + std::to_string(2 + number_of_tapes + 2 * number_of_tapes) + " campos validos.");
      }
    }

    Symbols antecedent_symbols;
    for (int i{1}; i <= number_of_tapes; ++i) {
      antecedent_symbols.push_back(production_data[i].front());
    }
    TransitionAntecedent antecedent{production_data[0], antecedent_symbols};
    State next_state = production_data[number_of_tapes + 1];
    std::vector<Movement> transition_movements;

    try {
      for (int i{number_of_tapes + 2}; i < 2 + number_of_tapes + 2 * number_of_tapes; i += 2) {
        Movement new_movement = {production_data[i].front(), StringToTapeMovement(production_data[i + 1])};
        transition_movements.emplace_back(new_movement);
      }
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
      throw InvalidTransitionError("Transicion mal formada: se esperaban " + std::to_string(2 + number_of_tapes + 2 * number_of_tapes) + " campos validos.");
    }
    TransitionConsequent consequent{transition_id++, next_state, transition_movements};
    this->transition_table_[antecedent] = consequent;
  }
}

/**
 * @brief Given a tape movement, returns its name.
 * 
 * @param movement Movement whose name will be returned.
 * @return std::string 
 */
std::string MovementToString(TapeMovement movement) {
  switch (movement) {
    case TapeMovement::RIGHT: return "R";
    case TapeMovement::LEFT:  return "L";
    case TapeMovement::STOP:  return "S";
    default:                  return "?";
  }
}

}