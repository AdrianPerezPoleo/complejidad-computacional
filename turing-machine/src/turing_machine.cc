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

/**
 * @brief Method that process an input string and simulates the behaviour of the Turing Machine.
 * 
 * @param word Word to be processed.
 */
void TuringMachine::Process(const std::string& word, std::ostream& os) {
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

  os << "\nContenido de las cintas:\n";
  tapes_.PrintTapes(os);
  os << "\n";
  os << "La MT se ha parado en el estado " << state_manager_.GetCurrentState() << ". ";
  if (state_manager_.IsInAcceptingState()) {
    os << "Es un estado de aceptación.\n";
  } else {
    os << "No es un estado de aceptación.\n";
  }
}

}