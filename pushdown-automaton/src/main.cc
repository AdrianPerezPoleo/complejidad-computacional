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

#include <iostream>
#include <set>
#include <vector>

#include "../include/automaton_configuration_reader.h"
#include "../include/pushdown_automaton.h"
#include "../include/program_options.h"

ProgramOptions ProcessParameters(const int argc, char* argv[]) {
  ProgramOptions options;
  bool config_found = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-config") {
      if (i + 1 < argc) {
        options.program_file = argv[++i];
        config_found = true;
      } else {
        std::cerr << "Error: La opción -config requiere la ruta a un fichero." << std::endl;
        std::exit(EXIT_FAILURE);
      }
    } else if (arg == "-trace") {
      if (i + 1 < argc) {
        std::string val = argv[++i];
        if (val == "y" || val == "Y") {
          options.trace_mode = true;
        } else if (val == "n" || val == "N") {
          options.trace_mode = false;
        } else {
          std::cerr << "Error: La opción -trace solo acepta 'y' o 'n' (se recibió '" << val << "')." << std::endl;
          std::exit(EXIT_FAILURE);
        }
      }
    } else {
      std::cerr << "Error: Opción desconocida '" << arg << "'." << std::endl;
    }
  }

  if (!config_found) {
    std::cerr << "Uso: " << argv[0] << " -config <fichero_configuracion.pda> [-trace]" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return options;
}

int main(const int argc, char* argv[]) {
  ProgramOptions options;
  try {
    options = ProcessParameters(argc, argv);
  } catch (...) {
    return 1;
  }

  AutomatonConfigurationReader reader(options.program_file);
  AutomatonConfiguration configuration = reader.ReadConfiguration();

  // Mejorar el procesamiento de parámetros de la terminal con los flagas adecuados

  PushdownAutomaton automaton(configuration, options.trace_mode);
  while (true) {
    std::cout << "Introduzca una cadena a procesar:\n";
    std::string string_to_verify;
    std::cin >> string_to_verify;
    if (automaton.Accepts(string_to_verify)) {
      std::cout << "\nAccepted" << std::endl; 
    } else {
      std::cout << "\nRejected" << std::endl;
    }
  }

  return 0;
}