/**
 * @file pushdown_automaton.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that simulates a pushdown automaton.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PUSHDOWN_AUTOMATON
#define PUSHDOWN_AUTOMATON

#include "automaton_configuration.h"
#include "automaton_stack.h"
#include "tape.h"
#include "state_manager.h"
#include "transition_table.h"

class PushdownAutomaton {
 public:
  PushdownAutomaton(const AutomatonConfiguration& configuration) {
    this->stack_ = AutomatonStack(configuration.initial_stack_symbol, configuration.stack_alphabet);
    this->tape_ = Tape(configuration.tape_alphabet);
    this->state_manager_ = StateManager(configuration.initial_state, configuration.automaton_states);
    this->transition_table_ = TransitionTable(configuration.transition_table);
  }

  bool Simulate(std::vector<Symbol> new_string) const;
 private:
  AutomatonStack stack_;
  Tape tape_;
  StateManager state_manager_;
  TransitionTable transition_table_;  
};

#endif