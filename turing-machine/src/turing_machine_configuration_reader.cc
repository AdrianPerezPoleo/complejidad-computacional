/**
 * @file turing_machine_configuration_reader.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the TuringMachineConfigurationReader class.
 * @version 1.0
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/turing_machine_configuration_reader.h"
#include "../include/turing_machine_error.h"

namespace turing {

/**
 * @brief Reads the file and builds the full TuringMachineConfiguration object.
 * 
 * @return TuringMachineConfiguration with parsed components and TransitionTable.
 */
TuringMachineConfiguration TuringMachineConfigurationReader::ReadConfiguration() {
  std::ifstream file(filepath_);
  if (!file.is_open()) {
    throw ConfigurationFileError("No se pudo abrir el archivo de configuracion: " + filepath_);
  }

  std::set<State> possible_states = ParseStates(file);
  Alphabet input_alphabet           = ParseAlphabet(file);
  Alphabet tape_alphabet          = ParseAlphabet(file);
  State initial_state              = ParseSingleToken<State>(file);
  Symbol blank_symbol              = ParseSingleToken<Symbol>(file);
  std::set<State> accepting_states = ParseStates(file);
  int number_of_tapes              = ParseSingleToken<int>(file);
  TransitionTable transition_table = ParseTransitionTable(file, number_of_tapes);

  file.close();

  if (possible_states.empty()) {
    throw InvalidConfigurationError("La configuracion no contiene estados.");
  }
  if (initial_state.empty() || !possible_states.contains(initial_state)) {
    throw InvalidConfigurationError("El estado inicial no esta definido en el conjunto de estados.");
  }
  if (!tape_alphabet.ContainsSymbol(blank_symbol)) {
    throw InvalidConfigurationError("El simbolo blanco no se encuentra en el alfabeto de cinta.");
  }

  for (const State& state : accepting_states) {
    if (!possible_states.contains(state)) {
      throw InvalidConfigurationError("El estado de aceptación " + std::string(state) + " no existe.");
    }
  }

  return TuringMachineConfiguration{
      possible_states,
      input_alphabet,
      tape_alphabet,
      initial_state,
      blank_symbol,
      accepting_states,
      number_of_tapes,
      transition_table
  };
}

/**
 * @brief Helper method to skip comment lines and blank lines.
 */
std::string TuringMachineConfigurationReader::GetNextValidLine(std::ifstream& file) const {
  std::string line;
  while (std::getline(file, line)) {
    line = line.substr(0, line.find('#')); // Removes the string characters after a #.
    
    // Checks if the line has at least one character that is not a space or tab.
    if (line.find_first_not_of(" \t\r\n") != std::string::npos) {
      return line;
    }
  }
  return "";
}

/**
 * @brief Reads and stres the states introduced in an automaton configuration file.
 * 
 * @param file File to be read.
 * @return std::set<State> Set of states the automaton has.
 */
std::set<State> TuringMachineConfigurationReader::ParseStates(std::ifstream& file) const {
  std::set<State> states;
  std::stringstream ss(GetNextValidLine(file));
  State state;
  while (ss >> state) {
    states.insert(state);
  }
  return states;
}

/**
 * @brief Method used to parse an alphabet of symbols. It will be used to read the tape and the stack alphabets.
 * 
 * @param file Stream containing the file information.
 * @return Alphabet instance containing the allowed symbols.
 */
Alphabet TuringMachineConfigurationReader::ParseAlphabet(std::ifstream& file) const {
  std::set<Symbol> symbols;
  std::stringstream ss(GetNextValidLine(file));
  Symbol symbol;
  while (ss >> symbol) {
    symbols.insert(symbol);
  }
  return Alphabet(symbols);
}

/**
 * @brief Method that reads a matrix containing the information of a transition table and returns
 *        a TransitionTable objetc with that information.
 * 
 * @param file Stream of the file being read.
 * @return TransitionTable containing all the transitions of the automaton.
 */
TransitionTable TuringMachineConfigurationReader::ParseTransitionTable(std::ifstream& file, int number_of_tapes) const {
  std::vector<std::vector<std::string>> transition_matrix;
  std::string line;

  while (!(line = GetNextValidLine(file)).empty()) {
    std::stringstream ss(line);
    std::vector<std::string> row;
    std::string token;
    while (ss >> token) {
      row.emplace_back(token);
    }
    if (!row.empty()) {
      transition_matrix.emplace_back(row);
    }
  }

  return TransitionTable(number_of_tapes, transition_matrix);
}

}