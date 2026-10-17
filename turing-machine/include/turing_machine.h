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
#include "multitape.h"
#include "state_manager.h"
#include "transition_table.h"

namespace turing {

class TuringMachine {
 public:
  TuringMachine(const TuringMachineConfiguration& configuration)
      : tapes_(configuration.number_of_tapes, configuration.tape_alphabet),
        state_manager_(configuration.initial_state, configuration.possible_states, configuration.accepting_states),
        transition_table_(configuration.transition_table)
    {
 //   VerifyTransitionTable(configuration);
  }

  bool Accepts(const std::string&);
 private:
  Multitape tapes_;
  StateManager state_manager_;
  TransitionTable transition_table_;

//  void VerifyTransitionTable(const AutomatonConfiguration&) const;
  void Restart() { tapes_.Restart(); state_manager_.Restart(); }
};

}

#endif