/**
 * @file tape.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the method needed by each tape of the Turing machine.
 * @version 1.0
 * @date 2026-10-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdexcept>
#include <iostream>
#include "../include/tape.h"

namespace turing {

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
Symbol Tape::Read() const {
  try {
    return this->tape_.at(head_);
  } catch (const std::out_of_range& exception) {
    return kEmptySymbol;
  }
}

void Tape::Write(const Symbol& symbol) {
  if (this->alphabet_.ContainsSymbol(symbol)) {
    try {
      this->tape_.at(head_) = symbol;
    } catch (std::out_of_range& error) {
      this->tape_ += symbol;
    }   
  } else {
    throw InvalidAlphabetError("Inserting the symbol " + std::to_string(symbol) + " in the tape is not allowed.");
  }
}

/**
 * @brief Displays the symbols that the tape still has to read.
 * 
 * @param os Output stream.
 * @return std::ostream& 
 */
std::ostream& Tape::PrintTape(std::ostream& os) const {
  std::string tape_symbols = "";
  for (int i{0}; i < (int)tape_.size(); ++i) {
    tape_symbols += this->tape_.at(i);
    if (head_ == i) {
      tape_symbols += "ñ";
    }
  }
  if (tape_symbols == "")
    tape_symbols = "-";
  os << tape_symbols;
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

/**
 * @brief Moves the head of the tape to the given direction.
 * 
 * @param movement Movement associated to a direction. 
 */
void Tape::Move(const TapeMovement& movement) {
  switch (movement) {
    case turing::TapeMovement::LEFT:
      if (head_ == 0) {
        tape_ = kEmptySymbol + tape_;
      } else {
        --head_;
      }
      break;
    case turing::TapeMovement::RIGHT:
      if (head_ == tape_.size() - 1) {
        tape_ += kEmptySymbol;
      }
      ++head_;
      break;
    case turing::TapeMovement::STOP:
      break;
    default:
    break;
  }
}

}