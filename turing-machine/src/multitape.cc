/**
 * @file multitape.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the Multitape class.
 * @version 1.0
 * @date 2026-10-16
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/multitape.h"

namespace turing {

  /**
   * @brief Assigns the given movements to the chosen tapes.
   * 
   * @param movements Vector containing the movements to execute.
   */
void Multitape::Move(const std::vector<Movement>& movements) {
  if (movements.size() != multitape_.size()) {
    // Lanzar error de número incorrecto de movimientos
  }
  for (int i{0}; i < movements.size(); ++i) {
    multitape_[i].ExecuteMovement(movements[i]);
  }
}

/**
 * @brief Restarts the multitape with its initial position.
 * 
 */
void Multitape::Restart() {
  for (Tape& tape : multitape_) {
    tape.Restart();
  }
}

void Multitape::PrintTapes() const {
  std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
  for (const Tape& tape : multitape_) {
    tape.PrintTape(std::cout);
    std::cout << std::endl;
  }
  std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
}

Symbols Multitape::GetCurrentSymbols() const {
  Symbols symbols;
  for (const Tape& tape : this->multitape_) {
    symbols.push_back(tape.Read());
  }
  return symbols;
}

};
