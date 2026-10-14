/**
 * @file turing_machine.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that simulates a Turing Machine.
 * @version 1.0
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TURING_MACHINE
#define TURING_MACHINE

#include "turing_machine_configuration_reader.h"
#include "tape.h"
#include "state_manager.h"
// #include "transition_table.h"

namespace turing {

class PushdownAutomaton {
 public:
  PushdownAutomaton(const TuringMachineConfiguration& configuration, bool trace_mode)
      : tape_(configuration.tape_alphabet),
        state_manager_(configuration.initial_state, configuration.possible_states, configuration.accepting_states)
  //      transition_table_(configuration.transition_table),
    {
 //   VerifyTransitionTable(configuration);
  }

  bool Accepts(const std::string&);
 private:
  Tape tape_;
  StateManager state_manager_;
//  TransitionTable transition_table_;

//  void VerifyTransitionTable(const AutomatonConfiguration&) const;
  void Restart() { tape_.Restart(); }
};

}

#endif