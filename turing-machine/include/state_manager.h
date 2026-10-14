/**
 * @file state_manager.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that stores the current state of the Turing machine.
 * @version 1.0
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef STATE_MANAGER
#define STATE_MANAGER

#include <string>
#include <set>

#include "alphabet.h"
#include "types.h"

namespace turing {
  
class StateManager {
 public:
  StateManager(const State& initial_state, const std::set<State>& possible_states)
  : initial_state_{initial_state}, possible_states_{possible_states} { }

  State GetInitialState() const { return initial_state_; }
  bool IsValidState(const State& state) const { 
    return possible_states_.contains(state); 
  }

 private:
  State initial_state_;
  std::set<State> possible_states_;
};

}

#endif