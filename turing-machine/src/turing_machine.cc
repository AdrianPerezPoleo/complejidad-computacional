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
  this->multitape_.InsertString(word);

  Transition next_transition;

  while (true) {
    State current_state = state_manager_.GetCurrentState();
    Symbols current_symbols = multitape_.GetCurrentSymbols();
    try {
      auto transition = transition_table_.GetTransition(current_state, current_symbols);
      state_manager_.ChangeToState(transition.consequent.next_state);
      multitape_.Move(transition.consequent.movements);
    } catch (std::out_of_range&) {
      break;
    }
  }

  os << "\nContenido de las cintas:\n";
  multitape_.PrintTapes(os);
  os << "\n";
  os << "La MT se ha parado en el estado " << state_manager_.GetCurrentState() << ". ";
  if (state_manager_.IsInAcceptingState()) {
    os << "Es un estado de aceptación.\n";
  } else {
    os << "No es un estado de aceptación.\n";
  }
}


/**
 * @brief Method that verifies if the transition table can be used by the given automaton.
 * 
 * @param configuration Struct containing the automaton configuration.
 */
void TuringMachine::VerifyTransitionTable(const TuringMachineConfiguration& configuration) const {
  for (const auto& transition : transition_table_.GetAllTransitions()) {
    const auto& antecedent = transition.antecedent;
    const auto& consequent = transition.consequent;

    if (configuration.possible_states.count(antecedent.previous_state) == 0) {
      throw InvalidTransitionError("El estado de origen '" + antecedent.previous_state +
                                   "' de una transicion no pertenece a la MT.");
    }
    if (configuration.possible_states.count(consequent.next_state) == 0) {
      throw InvalidTransitionError("El estado de destino '" + consequent.next_state +
                                   "' de una transicion no pertenece a la MT.");
    }
    for (const Symbol& tape_symbol : antecedent.tape_symbols) {
      if (tape_symbol != configuration.blank_symbol &&
          !configuration.tape_alphabet.ContainsSymbol(tape_symbol)) {
        throw InvalidTransitionError(std::string("El simbolo de cinta '") + tape_symbol +
                                    "' de una transicion no pertenece al alfabeto de cinta.");
      }
    }

    for (const Movement& movement : consequent.movements) {
      if (!configuration.tape_alphabet.ContainsSymbol(movement.next_symbol)) {
        throw InvalidTransitionError(std::string("El símbolo '") + movement.next_symbol +
                                    "' del consecuente de una transicion no pertenece al alfabeto de cinta.");        
      }
    }
  }
}

}