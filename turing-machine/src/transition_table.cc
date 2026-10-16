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

Transition TransitionTable::GetTransition(const State& current_state, const Symbols& tape_symbols) {
  if (transition_table_.contains({current_state, tape_symbols})) {
    auto consequent = transition_table_.at({current_state, tape_symbols});
    return {{current_state, tape_symbols}, consequent};
  } 
  throw std::out_of_range("Error: No existe una transicion definida para el estado y simbolos dados.");
}

void TransitionTable::InitializeTable(int number_of_tapes, const std::vector<std::vector<std::string>>& table_data_) {
  int transition_id = 1;
  for (const auto& production_data : table_data_ ) {
    for (int i{0}; i < (number_of_tapes + 1) * 2; ++i) {
      if (production_data[i].empty()) {
        throw InvalidTransitionError("Transicion mal formada: se esperaban" + std::to_string((number_of_tapes + 1) * 2) + "campos validos.");
      }
    }

    TransitionAntecedent antecedent{production_data[0], production_data[1]};
    State next_state = production_data[2];
    std::vector<Movement> transition_movements;

    try {
      for (int i{3}; i < (number_of_tapes + 1) * 2; i += 2) {
        Movement new_movement = {production_data[i].front(), StringToTapeMovement(production_data[i + 1])};
        transition_movements.emplace_back(new_movement);
      }
    } catch (std::exception& e) {
      throw InvalidTransitionError("Transicion mal formada: se esperaban" + std::to_string((number_of_tapes + 1) * 2) + "campos validos.");
    }
    TransitionConsequent consequent{transition_id++, next_state, transition_movements};
    this->transition_table_[antecedent] = consequent;
  }
}

std::string MovementToString(TapeMovement movement) {
  switch (movement) {
    case TapeMovement::RIGHT: return "R";
    case TapeMovement::LEFT:  return "L";
    case TapeMovement::STOP:  return "S";
    default:                  return "?";
  }
}

void TransitionTable::Print(std::ostream& os) const {
  os << "=== Transition Table (Tapes: " << number_of_tapes_ << ") ===\n";

  for (const auto& [antecedent, consequent] : transition_table_) {
    os << "δ(" << antecedent.previous_state << ", [";
    for (size_t i = 0; i < antecedent.tape_symbols.size(); ++i) {
      os << antecedent.tape_symbols[i] << (i + 1 < antecedent.tape_symbols.size() ? ", " : "");
    }
    os << "]) -> ";

    os << "State: " << consequent.next_state << " | Actions: [";
    for (size_t i = 0; i < consequent.movements.size(); ++i) {
      os << "(" << consequent.movements[i].next_symbol << ", "
         << MovementToString(consequent.movements[i].movement) << ")"
         << (i + 1 < consequent.movements.size() ? ", " : "");
    }
    os << "]\n";
  }
  
  os << "========================================\n";
}

}