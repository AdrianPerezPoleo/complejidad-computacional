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
 * @brief Introduces a new string into the tape, removing the content that was before.
 * 
 * @param new_string New string to introduce.
 */
bool Tape::IntroduceString(const std::string& new_string) {
  if (this->IsValid(new_string)) {
    tape_ = new_string;
    head_ = 0;
    return true;
  } else {
    tape_.clear();
    head_ = 0;
    return false;
  }
}

/**
 * @brief Gets the next symbol in the tape, advancing the head. 
 *        If there is no symbol, the empty symbol is returned.
 * 
 * @return Symbol Read symbol from the tape.
 */
Symbol Tape::GetNextSymbol() const {
  try {
    return this->tape_.at(head_);
  } catch (const std::out_of_range& exception) {
    return kEmptySymbol;
  }
}

/**
 * @brief Displays the symbols that the tape still has to read.
 * 
 * @param os Output stream.
 * @return std::ostream& 
 */
std::ostream& Tape::PrintSymbolsLeft(std::ostream& os) const {
  std::string symbols_left = "";
  for (size_t i{head_}; i < tape_.size(); ++i) {
    symbols_left += tape_[i];
  }
  if (symbols_left == "")
    symbols_left = "-";
  os << symbols_left;
  return os;
}

/**
 * @brief Checks if the symbols in the tape are valid.
 * 
 * @param tape Vector containing the symbols of the tape.
 * @param alphabet Set of symbols allowed.
 * @return true if the tape is valid.
 * @return false otherwise.
 */
bool Tape::IsValid(const std::string& tape) const {
  if (tape == std::to_string(kEmptySymbol)) return true;
  for (const auto& symbol : tape) {
    if (!this->alphabet_.ContainsSymbol(symbol)) return false;
  }
  return true;
}