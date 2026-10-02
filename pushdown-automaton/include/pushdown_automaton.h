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

#include "automaton_configuration_reader.h"
#include "automaton_stack.h"
#include "tape.h"
#include "state_manager.h"
#include "transition_table.h"

namespace pda {
  
class PushdownAutomaton {
 public:
  PushdownAutomaton(const AutomatonConfiguration& configuration, bool trace_mode)
      : stack_(configuration.initial_stack_symbol, configuration.stack_alphabet),
        tape_(configuration.tape_alphabet),
        state_manager_(configuration.initial_state, configuration.automaton_states),
        transition_table_(configuration.transition_table),
        trace_mode_{trace_mode} {
    VerifyTransitionTable(configuration);
  }

  bool Accepts(const std::string&);
 private:
  AutomatonStack stack_;
  Tape tape_;
  StateManager state_manager_;
  TransitionTable transition_table_;

  bool trace_mode_;

  void VerifyTransitionTable(const AutomatonConfiguration&) const;
  bool CanAccept(const State&, const Tape&, const AutomatonStack&);
  void Restart() { stack_.Restart(); tape_.Restart(); }
};

}

#endif