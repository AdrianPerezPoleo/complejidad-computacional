/**
 * @file automaton_configuration.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Configuration used to create a pushdown automaton.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AUTOMATON_CONFIGURATION
#define AUTOMATON_CONFIGURATION

#include <set>
#include <string>

#include "alphabet.h"
#include "transition_table.h"

struct AutomatonConfiguration {
  std::set<State> automaton_states;
  Alphabet tape_alphabet;
  Alphabet stack_alphabet;
  State initial_state;
  Symbol initial_stack_symbol;
  TransitionTable transition_table;
};

#endif