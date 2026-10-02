/**
 * @file input_reader.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Reads an automaton configuration file.
 * @version 1.0
 * @date 27-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AUTOMATON_CONFIGURATION_READER
#define AUTOMATON_CONFIGURATION_READER

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "alphabet.h"
#include "transition_table.h"

namespace pda {

struct AutomatonConfiguration {
  std::set<State> automaton_states;
  Alphabet tape_alphabet;
  Alphabet stack_alphabet;
  State initial_state;
  Symbol initial_stack_symbol;
  TransitionTable transition_table;
};

class AutomatonConfigurationReader {
 public:
  AutomatonConfigurationReader(const std::string& filepath) : filepath_{filepath} {}

  AutomatonConfiguration ReadConfiguration();
 private:
  std::string filepath_;

  std::string GetNextValidLine(std::ifstream& file) const;
  std::set<State> ParseStates(std::ifstream& file) const;
  Alphabet ParseAlphabet(std::ifstream& file) const;
  TransitionTable ParseTransitionTable(std::ifstream& file) const;

  template <typename T>
  T ParseSingleToken(std::ifstream& file) const {
    T token{};
    std::stringstream(GetNextValidLine(file)) >> token;
    return token;
  } 
};

}

#endif