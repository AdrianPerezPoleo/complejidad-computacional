/**
 * @file turing_machine.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implements the Turing Machine simulator.
 * @version 1.0
 * @date 2026-10-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/turing_machine.h"

namespace turing {

bool TuringMachine::Accepts(const std::string& word) {
  this->Restart();
  this->tapes_.InsertString(word);

  Transition next_transition;

  while (true) {
    State current_state = state_manager_.GetCurrentState();
    Symbols current_symbols = tapes_.GetCurrentSymbols();
    try {
      auto transition = transition_table_.GetTransition(current_state, current_symbols);
      state_manager_.ChangeToState(transition.consequent.next_state);
      tapes_.Move(transition.consequent.movements);
    } catch (std::out_of_range&) {
      break;
    }
  }

  tapes_.PrintTapes();
  if (state_manager_.IsInAcceptingState()) return true;
  return false;
}

}