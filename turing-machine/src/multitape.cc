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
 */
void Multitape::Restart() {
  for (Tape& tape : multitape_) {
    tape.Restart();
  }
}

/**
 * @brief Print the tapes in the multitape.
 */
void Multitape::PrintTapes(std::ostream& os) const {
  for (const Tape& tape : multitape_) {
    tape.PrintTape(os);
    os << std::endl;
  }
}

/**
 * @brief Returns the symbols pointed by each tape head.
 * 
 * @return Symbols that are being pointed by each tape head.
 */
Symbols Multitape::GetCurrentSymbols() const {
  Symbols symbols;
  for (const Tape& tape : this->multitape_) {
    symbols.push_back(tape.Read());
  }
  return symbols;
}

};
