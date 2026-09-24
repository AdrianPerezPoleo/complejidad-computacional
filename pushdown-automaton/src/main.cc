/**
 * @file main.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Main program that simulates the pushdown automata.
 * @version 0.1
 * @date 2026-09-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include <set>
#include <vector>

#include "../include/automaton_configuration.h"
#include "../include/tape.h"
#include "../include/automaton_stack.h"
#include "../include/state_manager.h"

int main() {
  Alphabet tape_alphabet({'a', 'b'});
  Alphabet stack_alphabet({'0', '1', 'Z'});
  Symbol initial_stack_symbol = 'Z';
  std::set<State> possible_states = {"q0", "q1", "qf"};
  State initial_state = "q0";

  AutomatonConfiguration configuration{
      possible_states,
      tape_alphabet,
      stack_alphabet,
      initial_state,
      initial_stack_symbol,
      TransitionTable({
          {"q0", "1", "q0", "a", "Z"},
          {"q0", "010", "q1", "b", "1"},
          {"q1", "100", "qf", "b", "0Z"},
      })};

  std::cout << "Pushdown Automaton Configuration" << std::endl;
  std::cout << "Initial state: " << configuration.initial_state << std::endl;
  std::cout << "Initial stack symbol: " << configuration.initial_stack_symbol
            << std::endl;
  std::cout << "States: ";
  for (const auto& state : configuration.automaton_states) {
    std::cout << state << ' ';
  }
  std::cout << std::endl;

  std::cout << "Transition table:" << std::endl;
  configuration.transition_table.PrintTransitions();

  Tape tape({'a', 'a', 'a'}, tape_alphabet);
  std::cout << "Tape: " << tape.GetNextSymbol() << tape.GetNextSymbol() << tape.GetNextSymbol() << tape.GetNextSymbol() << std::endl;

  AutomatonStack stack(initial_stack_symbol, stack_alphabet);
  stack.Push('0');
  std::cout << stack.Top() << std::endl;
  stack.Push("Z10");
  std::cout << stack.Top() << std::endl;

  StateManager state_manager(initial_state, possible_states);
  std::cout << state_manager.GetCurrentState() << std::endl;

  state_manager.ChangeToState("qf");
  std::cout << state_manager.GetCurrentState() << std::endl;

  state_manager.ChangeToState("rt");
  std::cout << state_manager.GetCurrentState() << std::endl;

  return 0;
}