/**
 * @file main.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Main function of the program.
 * @version 1.0
 * @date 2026-10-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include "../include/program_options.h"
#include "../include/power.h"

int main(int argc, char* argv[]) {
  try {
    ProgramOptions options = ProcessParameters(argc, argv);
    Power power_calculator;
    PrimitiveRecursiveFunction::ResetCallCount();
    int result = power_calculator(options.base, options.exponent);
    std::cout << "Resultado: " << result << std::endl
              << "Número de llamadas: " << PrimitiveRecursiveFunction::GetCallCount() << std::endl;
  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
}