/**
 * @file program_options.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the function that collects the user's program options.
 * @version 1.0
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>

#include "../include/program_options.h"

/**
 * @brief Prints an error (if needed) and shows the user how to execute the program.
 * 
 * @param program_name Name of the current program.
 * @param error_msg Error message to be displayed (if needed)
 */
void PrintUsageAndExit(const std::string& program_name, const std::string& error_msg = "") {
  if (!error_msg.empty()) {
    std::cerr << "Error: " << error_msg << std::endl;
  }
  std::cerr << "Uso: " << program_name << " -config <fichero>" << std::endl;
  std::exit(EXIT_FAILURE);
}

/**
 * @brief Checks if the -config option is correctly introduced and stores its information. 
 * 
 * @param i Number of argument being checked.
 * @param argc Number of parameters given.
 * @param argv Parameters given by the user.
 * @param options Object containing the options introduced by the user.
 * @param config_found True if the configuration flag has been found. False otherwise.
 */
void ParseConfigOption(int& i, int argc, char* argv[], ProgramOptions& options, bool& config_found) {
  if (i + 1 < argc) {
    options.program_file = argv[++i];
    config_found = true;
  } else {
    PrintUsageAndExit(argv[0], "La opción -config requiere la ruta a un fichero.");
  }
}

/**
 * @brief Method that reads the parameters given by the user and checks the have been correctly introduced.
 * 
 * @param argc Number of parameters given.
 * @param argv List containing the given parameters.
 * @return ProgramOptions 
 */
ProgramOptions ProcessParameters(const int argc, char* argv[]) {
  ProgramOptions options;
  bool config_found = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-config") {
      ParseConfigOption(i, argc, argv, options, config_found);
    } else {
      PrintUsageAndExit(argv[0], "Opción desconocida '" + arg + "'.");
    }
  }

  if (!config_found) {
    PrintUsageAndExit(argv[0], "Falta el argumento obligatorio -config.");
  }

  return options;
}