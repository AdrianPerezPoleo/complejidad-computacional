/**
 * @file automaton_configuration_reader.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the AutomatonConfigurationReader class.
 * @version 1.0
 * @date 27-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/automaton_configuration_reader.h"
#include "../include/automaton_error.h"

namespace pda {

/**
 * @brief Reads the file and builds the full AutomatonConfiguration object.
 * 
 * @return AutomatonConfiguration with parsed components and TransitionTable.
 */
pda::AutomatonConfiguration AutomatonConfigurationReader::ReadConfiguration() {
  std::ifstream file(filepath_);
  if (!file.is_open()) {
    throw ConfigurationFileError("No se pudo abrir el archivo de configuracion: " + filepath_);
  }

  std::set<State> automaton_states = ParseStates(file);
  Alphabet tape_alphabet           = ParseAlphabet(file);
  Alphabet stack_alphabet          = ParseAlphabet(file);
  State initial_state              = ParseSingleToken<State>(file);
  Symbol initial_stack_symbol      = ParseSingleToken<Symbol>(file);
  TransitionTable transition_table = ParseTransitionTable(file);

  if (automaton_states.empty()) {
    throw InvalidConfigurationError("La configuracion no contiene estados.");
  }
  if (initial_state.empty() || automaton_states.count(initial_state) == 0) {
    throw InvalidConfigurationError("El estado inicial no esta definido en el conjunto de estados.");
  }
  if (!stack_alphabet.ContainsSymbol(initial_stack_symbol)) {
    throw InvalidConfigurationError("El simbolo inicial de la pila no pertenece al alfabeto de pila.");
  }

  file.close();
  return AutomatonConfiguration{
      automaton_states,
      tape_alphabet,
      stack_alphabet,
      initial_state,
      initial_stack_symbol,
      transition_table
  };
}

/**
 * @brief Helper method to skip comment lines and blank lines.
 */
std::string AutomatonConfigurationReader::GetNextValidLine(std::ifstream& file) const {
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
std::set<State> AutomatonConfigurationReader::ParseStates(std::ifstream& file) const {
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
Alphabet AutomatonConfigurationReader::ParseAlphabet(std::ifstream& file) const {
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
TransitionTable AutomatonConfigurationReader::ParseTransitionTable(std::ifstream& file) const {
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

  return TransitionTable(transition_matrix);
}

}