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
 * @brief Construct a new Tape:: Tape object
 * 
 * @param tape Vector containing the symbols in the tape.
 * @param tape_alphabet Set of symbols the tape can have.
 */
Tape::Tape(const std::vector<Symbol> tape, const Alphabet& tape_alphabet) : head_{0} {
  if (this->IsValid(tape, tape_alphabet)) {
    tape_ = tape;
  } else {
    // Lanzar un error
  }
}

/**
 * @brief Checks if the symbols in the tape are valid.
 * 
 * @param tape Vector containing the symbols of the tape.
 * @param alphabet Set of symbols allowed.
 * @return true if the tape is valid.
 * @return false otherwise.
 */
bool Tape::IsValid(const std::vector<Symbol>& tape, const Alphabet& alphabet) const {
  for (const auto& symbol : tape) {
    if (!alphabet.ContainsSymbol(symbol)) return false;
  }
  return true;
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

