/**
 * @file state_manager.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that stores the current state of the automaton.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef STATE_MANAGER
#define STATE_MANAGER

#include <string>
#include <set>

#include "alphabet.h"

using State = std::string;

class StateManager {
 public:
  StateManager(const State& initial_state, const std::set<State>& possible_states): possible_states_{possible_states} { 
    this->ChangeToState(initial_state);
  }

  State GetCurrentState() const { return current_state_; }
  void ChangeToState(const State& new_state) { 
    if (IsValidState(new_state)) this->current_state_ = new_state;
    // else // Lanzar algún error
  }
 private:
  State current_state_;
  std::set<State> possible_states_;

  bool IsValidState(const State& state) const { return possible_states_.find(state) != possible_states_.end(); }
};

#endif