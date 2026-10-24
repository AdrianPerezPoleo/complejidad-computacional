/**
 * @file program_options.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementatin of the function that collects the user's program options.
 * @version 1.0
 * @date 29-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include <cstdlib> // Required for std::exit and EXIT_FAILURE

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
  std::cerr << "Uso: " << program_name << " -x <base_number> -y <exponent_number>" << std::endl;
  std::exit(EXIT_FAILURE);
}

/**
 * @brief Checks if the -x option is correctly introduced and stores its information. 
 * 
 * @param i Number of argument being checked.
 * @param argc Number of parameters given.
 * @param argv Parameters given by the user.
 * @param options Object containing the options introduced by the user.
 * @param base_found True if the base flag has been found. False otherwise.
 */
void ParseBase(int& i, int argc, char* argv[], ProgramOptions& options, bool& base_found) {
  if (i + 1 < argc) {
    try {
      options.base = std::stoi(argv[++i]);
      base_found = true;
    } catch (const std::invalid_argument& e) {
      PrintUsageAndExit(argv[0], "El valor introducido en -x no es un número válido.");
    } catch (const std::out_of_range& e) {
      PrintUsageAndExit(argv[0], "El número introducido en -x es demasiado grande.");
    }
  } else {
    PrintUsageAndExit(argv[0], "La opción -x requiere un número válido.");
  }
}

/**
 * @brief Checks if the -y option is correctly introduced and stores its information. 
 * 
 * @param i Number of argument being checked.
 * @param argc Number of parameters given.
 * @param argv Parameters given by the user.
 * @param options Object containing the options introduced by the user.
 * @param exponent_found True if the exponent flag has been found. False otherwise.
 */
void ParseExponent(int& i, int argc, char* argv[], ProgramOptions& options, bool& exponent_found) {
  if (i + 1 < argc) {
    try {
      options.exponent = std::stoi(argv[++i]);
      exponent_found = true;
    } catch (const std::invalid_argument& e) {
      PrintUsageAndExit(argv[0], "El valor introducido en -x no es un número válido.");
    } catch (const std::out_of_range& e) {
      PrintUsageAndExit(argv[0], "El número introducido en -x es demasiado grande.");
    }
  } else {
    PrintUsageAndExit(argv[0], "La opción -y requiere un número válido.");
  }
}

/**
 * @brief Method that reads the parameters given by the user and checks they have been correctly introduced.
 * 
 * @param argc Number of parameters given.
 * @param argv List containing the given parameters.
 * @return ProgramOptions 
 */
ProgramOptions ProcessParameters(const int argc, char* argv[]) {
  ProgramOptions options;
  bool base_found = false;
  bool exponent_found = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-x") {
      ParseBase(i, argc, argv, options, base_found);
    } else if (arg == "-y") {
      ParseExponent(i, argc, argv, options, exponent_found);
    } else {
      PrintUsageAndExit(argv[0], "Opción desconocida '" + arg + "'.");
    }
  }

  if (!base_found) {
    PrintUsageAndExit(argv[0], "Falta el argumento obligatorio -x.");
  }

  if (!exponent_found) {
    PrintUsageAndExit(argv[0], "Falta el argumento obligatorio -y.");
  }

  if (options.base < 0) {
    PrintUsageAndExit(argv[0], "La base debe ser un número natural.");
  }

  if (options.exponent < 0) {
    PrintUsageAndExit(argv[0], "El exponente debe ser un número natural.");
  }

  return options;
}