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
  StateManager(const State& initial_state, const std::set<State>& possible_states, const std::set<State>& accepting_states)
  : initial_state_{initial_state}, possible_states_{possible_states}, accepting_states_{accepting_states} { 
    current_state_ = initial_state;
  }

  State GetCurrentState() const { return current_state_; }
  bool IsValidState(const State& state) const { return possible_states_.contains(state); }

  void ChangeToState(const State& next_state) { if (this->IsValidState(next_state)) current_state_ = next_state; }
  bool IsInAcceptingState() const { return accepting_states_.contains(current_state_); }
  void Restart() { current_state_ = initial_state_; }
 private:
  State initial_state_;
  std::set<State> possible_states_;
  std::set<State> accepting_states_;
  State current_state_;
};

}

#endif