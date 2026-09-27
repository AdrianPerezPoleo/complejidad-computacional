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
  if (automaton.Accepts({"aabb"})) {
    std::cout << "Accepted" << std::endl;
  } else {
    std::cout << "Rejected" << std::endl;
  }

  return 0;
}