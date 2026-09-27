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

int main() {
  AutomatonConfigurationReader reader("../examples/configuration-3.txt");
  AutomatonConfiguration configuration = reader.ReadConfiguration();

  PushdownAutomaton automaton(configuration);
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