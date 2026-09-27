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

/**
 * @brief Simulates the behaviour of a pushdown automaton.
 * 
 * @param new_string String to verify if belongs to the language.
 * @return true if the string belongs to the language.
 * @return false otherwise.
 */
bool PushdownAutomaton::Accepts(const std::string& new_string) {
  transition_table_.PrintTransitions();
  this->Restart();
  Tape tape(this->tape_);
  tape.IntroduceString(new_string);

  AutomatonStack initial_stack(this->stack_);
  return CanAccept(state_manager_.GetInitialState(), tape, initial_stack);
}

bool PushdownAutomaton::CanAccept(const State& current_state, 
                                  const Tape& current_tape,   
                                  const AutomatonStack& current_stack) {
  std::cout << "State: " << current_state << "\t|Tape: "; 
  current_tape.PrintSymbolsLeft(std::cout) << "\t| Stack: "; 
  current_stack.PrintContent(std::cout) << "\t  | Available Transitions: ";
  if (!current_tape.HasSymbolsToRead() && current_stack.IsEmpty()) return true;
  if (current_stack.IsEmpty()) return false;

  Symbol current_stack_symbol = current_stack.Top();
  Symbol tape_symbol = current_tape.GetNextSymbol();

  const auto& possible_transitions = this->transition_table_.GetTransitions(current_state, tape_symbol, current_stack_symbol);
 
  for (const auto& transition : possible_transitions) {
    std::cout << transition.consequent.identifier << " ";
  }
  std::cout << std::endl;
  for (const auto& transition : possible_transitions) {
    AutomatonStack new_stack = current_stack;
    new_stack.Pop();
    new_stack.Push(transition.consequent.symbols_to_push);

    Tape new_tape = current_tape;
    if (transition.antecedent.current_tape_symbol != '.') {
      new_tape.Advance();
    }

    if (CanAccept(transition.consequent.next_state, new_tape, new_stack)) {
      return true;
   }
  }
  return false;
}