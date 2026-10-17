/**
 * @file main.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Main program that simulates the Turing machine.
 * @version 0.1
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>

#include "../include/multitape.h"
#include "../include/turing_machine_configuration_reader.h"
#include "../include/turing_machine_error.h"
#include "../include/program_options.h"
#include "../include/turing_machine.h"

int main(const int argc, char* argv[]) {
  try {
    ProgramOptions options = ProcessParameters(argc, argv);
    turing::TuringMachineConfigurationReader reader(options.program_file);
    turing::TuringMachineConfiguration configuration = reader.ReadConfiguration();

    turing::TuringMachine turing_machine(configuration);
    while (true) {
      std::cout << "Introduzca una cadena a procesar (O Ctrl + C para salir):\n";
      std::string string_to_verify;
      std::cin >> string_to_verify;
      if (turing_machine.Accepts(string_to_verify)) {
        std::cout << "\nAccepted" << std::endl;
      } else {
        std::cout << "\nRejected" << std::endl;
      }
    }
  } catch (const turing::TuringMachineError& error) {
    std::cerr << "Error: " << error.what() << std::endl;
    return 1;
  }
}