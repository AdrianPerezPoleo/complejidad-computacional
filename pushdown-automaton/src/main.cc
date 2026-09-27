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
#include "../include/pushdown_automaton.h"

int main() {
  std::set<State> possible_states = {"q1", "q2"};
  Alphabet tape_alphabet({'a', 'b'});
  Alphabet stack_alphabet({'S', 'A'});
  State initial_state = "q1";
  Symbol initial_stack_symbol = 'S';

  AutomatonConfiguration configuration{
      possible_states,
      tape_alphabet,
      stack_alphabet,
      initial_state,
      initial_stack_symbol,
      TransitionTable({
          {"q1", "a", "S", "q1", "A"},
          {"q1", "a", "A", "q1", "AA"},
          {"q1", "b", "A", "q2", "."},
          {"q2", "b", "A", "q2", "."}
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

  PushdownAutomaton automaton(configuration);
  if (automaton.Accepts({"aaabb"})) {
    std::cout << "Accepted" << std::endl;
  } else {
    std::cout << "Rejected" << std::endl;
  }

  return 0;
}