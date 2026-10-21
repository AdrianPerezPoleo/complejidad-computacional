/**
 * @file turing_machine_configuration_reader.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Reads a Turing machine configuration file.
 * @version 1.0
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TURING_MACHINE_CONFIGURATION_READER
#define TURING_MACHINE_CONFIGURATION_READER

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "alphabet.h"
 #include "transition_table.h"

namespace turing {

struct TuringMachineConfiguration {
  std::set<State> possible_states;
  Alphabet input_alphabet;
  Alphabet tape_alphabet;
  State initial_state;
  Symbol blank_symbol;
  std::set<State> accepting_states;
  int number_of_tapes;
  TransitionTable transition_table;
};

class TuringMachineConfigurationReader {
 public:
  TuringMachineConfigurationReader(const std::string& filepath) : filepath_{filepath} {}

  TuringMachineConfiguration ReadConfiguration();
 private:
  std::string filepath_;

  std::string GetNextValidLine(std::ifstream& file) const;
  std::set<State> ParseStates(std::ifstream& file) const;
  Alphabet ParseAlphabet(std::ifstream& file) const;
  TransitionTable ParseTransitionTable(std::ifstream& file, int) const;

  template <typename T>
  T ParseSingleToken(std::ifstream& file) const {
    T token{};
    std::stringstream(GetNextValidLine(file)) >> token;
    return token;
  } 
};

}

#endif