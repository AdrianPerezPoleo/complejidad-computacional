/**
 * @file tape.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of some methods of the tape inside the pushdown automaton.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdexcept>
#include <iostream>
#include "../include/tape.h"


/**
 * @brief Checks if the symbols in the tape are valid.
 * 
 * @param tape Vector containing the symbols of the tape.
 * @param alphabet Set of symbols allowed.
 * @return true if the tape is valid.
 * @return false otherwise.
 */
bool Tape::IsValid(const std::vector<Symbol>& tape) const {
  for (const auto& symbol : tape) {
    if (!this->alphabet_.ContainsSymbol(symbol)) return false;
  }
  return true;
}

void Tape::IntroduceString(const std::vector<Symbol>& new_string) {
  if (this->IsValid(new_string)) {
    tape_ = new_string;
  } else {
    // Lanzar error de símbolo no válido en la cinta
  }
}

/**
 * @brief Gets the next symbol in the tape, advancing the head. 
 *        If there is no symbol, the empty symbol is returned.
 * 
 * @return Symbol Read symbol from the tape.
 */
Symbol Tape::GetNextSymbol() {
  try {
    return this->tape_.at(head_++);
  } catch (const std::out_of_range& exception) {
    return this->kEmptySymbol;
  }
}

