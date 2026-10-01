/**
 * @file pushdown_automaton.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the pushdown automaton.
 * @version 1.0
 * @date 25-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/pushdown_automaton.h"
#include "../include/automaton_error.h"

/**
 * @brief Simulates the behaviour of a pushdown automaton.
 * 
 * @param new_string String to verify if belongs to the language.
 * @return true if the string belongs to the language.
 * @return false otherwise.
 */
bool PushdownAutomaton::Accepts(const std::string& new_string) {
  if (this->trace_mode_) transition_table_.PrintTransitions();
  this->Restart();
  Tape tape(this->tape_);
  if (!tape.IntroduceString(new_string)) return false;

  AutomatonStack initial_stack(this->stack_);
  return CanAccept(state_manager_.GetInitialState(), tape, initial_stack);
}

/**
 * @brief Auxiliar method that allows the implementation of the DFS to
 *        check if a word beblongs to an alphabet.
 * 
 * @param current_state Current state of the automaton
 * @param current_tape Tape that is being used by the automaton (with the head pointing to a position)
 * @param current_stack Stack being used by the automaton.
 * @return true if the automaton can accept the given word in the tape.
 * @return false otherwise.
 */
bool PushdownAutomaton::CanAccept(const State& current_state, 
                                  const Tape& current_tape,   
                                  const AutomatonStack& current_stack) {
  if (this->trace_mode_) {
    std::cout << "Estado: " << current_state << "\t| Cinta: "; 
    current_tape.PrintSymbolsLeft(std::cout) << "\t| Pila: "; 
    current_stack.PrintContent(std::cout) << "\t  | Transiciones Disponibles: ";
  }
  if (!current_tape.HasSymbolsToRead() && current_stack.IsEmpty()) return true;
  if (current_stack.IsEmpty()) return false;

  Symbol current_stack_symbol = current_stack.Top();
  Symbol tape_symbol = current_tape.GetNextSymbol();

  const auto& possible_transitions = this->transition_table_.GetTransitions(current_state, tape_symbol, current_stack_symbol);
 
  if (this->trace_mode_) {
    for (const auto& transition : possible_transitions) {
      std::cout << transition.consequent.identifier << " ";
    }
    std::cout << std::endl;
  }
  for (const auto& transition : possible_transitions) {
    AutomatonStack new_stack = current_stack;
    new_stack.Pop();
    new_stack.Push(transition.consequent.symbols_to_push);

    Tape new_tape = current_tape;
    if (transition.antecedent.current_tape_symbol != kEmptySymbol) {
      new_tape.Advance();
    }

    if (CanAccept(transition.consequent.next_state, new_tape, new_stack)) {
      return true;
   }
  }
  return false;
}

/**
 * @brief Method that verifies if the transition table can be used by the given automaton.
 * 
 * @param configuration Struct containing the automaton configuration.
 */
void PushdownAutomaton::VerifyTransitionTable(const AutomatonConfiguration& configuration) const {
  for (const auto& transition : transition_table_.GetAllTransitions()) {
    const auto& antecedent = transition.antecedent;
    const auto& consequent = transition.consequent;

    if (configuration.automaton_states.count(antecedent.current_state) == 0) {
      throw InvalidTransitionError("El estado de origen '" + antecedent.current_state +
                                   "' de una transicion no pertenece al automata.");
    }
    if (configuration.automaton_states.count(consequent.next_state) == 0) {
      throw InvalidTransitionError("El estado de destino '" + consequent.next_state +
                                   "' de una transicion no pertenece al automata.");
    }
    if (antecedent.current_tape_symbol != kEmptySymbol &&
        !configuration.tape_alphabet.ContainsSymbol(antecedent.current_tape_symbol)) {
      throw InvalidTransitionError(std::string("El simbolo de cinta '") + antecedent.current_tape_symbol +
                                   "' de una transicion no pertenece al alfabeto de cinta.");
    }
    if (!configuration.stack_alphabet.ContainsSymbol(antecedent.current_stack_symbol)) {
      throw InvalidTransitionError(std::string("El simbolo de pila '") + antecedent.current_stack_symbol +
                                   "' de una transicion no pertenece al alfabeto de pila.");
    }
    if (consequent.symbols_to_push != ".") {
      for (const Symbol symbol : consequent.symbols_to_push) {
        if (!configuration.stack_alphabet.ContainsSymbol(symbol)) {
          throw InvalidTransitionError(std::string("El simbolo '") + symbol +
                                       "' que se apila no pertenece al alfabeto de pila.");
        }
      }
    }
  }
}