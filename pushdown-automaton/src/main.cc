/**
 * @file main.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Main program that simulates the pushdown automata.
 * @version 0.1
 * @date 2026-09-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/automaton_configuration_reader.h"
#include "../include/automaton_error.h"
#include "../include/pushdown_automaton.h"
#include "../include/program_options.h"

int main(const int argc, char* argv[]) {
  try {
    ProgramOptions options = ProcessParameters(argc, argv);
    pda::AutomatonConfigurationReader reader(options.program_file);
    pda::AutomatonConfiguration configuration = reader.ReadConfiguration();

    pda::PushdownAutomaton automaton(configuration, options.trace_mode);
    while (true) {
      std::cout << "Introduzca una cadena a procesar (O Ctrl + C para salir):\n";
      std::string string_to_verify;
      std::cin >> string_to_verify;
      if (automaton.Accepts(string_to_verify)) {
        std::cout << "\nAccepted" << std::endl;
      } else {
        std::cout << "\nRejected" << std::endl;
      }
    }
  } catch (const pda::AutomatonError& error) {
    std::cerr << "Error: " << error.what() << std::endl;
    return 1;
  }
}