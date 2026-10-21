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

void Tape::ExecuteMovement(const Movement& movement) {
  this->Write(movement.next_symbol);
  this->Move(movement.movement);
}

/**
 * @brief Gets the next symbol in the tape, advancing the head. 
 *        If there is no symbol, the empty symbol is returned.
 * 
 * @return Symbol Read symbol from the tape.
 */
Symbol Tape::Read() const {
  if (head_ < tape_.size()) {
    return tape_[head_];
  }
  return blank_symbol_;
}

void Tape::Write(const Symbol& symbol) {
  if (!this->alphabet_.ContainsSymbol(symbol)) {
    throw InvalidAlphabetError("Inserting the symbol in the tape is not allowed.");
  }
  if (head_ >= tape_.size()) {
    tape_.resize(head_ + 1, blank_symbol_);
  }
  tape_[head_] = symbol;
}

/**
 * @brief Displays the symbols that the tape still has to read.
 * 
 * @param os Output stream.
 * @return std::ostream& 
 */
std::ostream& Tape::PrintTape(std::ostream& os) const {
  std::string result = "";
  size_t max_len = std::max(tape_.size(), static_cast<size_t>(head_ + 1));

  for (size_t i = 0; i < max_len; ++i) {
    char current_char = (i < tape_.size()) ? tape_[i] : blank_symbol_;
    if (head_ == i) {
      result += '[';
      result += current_char;
      result += ']';
    } else {
      result += current_char;
    }
  }

  os << result;
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
  if (tape.size() == 1 && tape[0] == blank_symbol_) return true;
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
        tape_ = blank_symbol_ + tape_;
      } else {
        --head_;
      }
      break;
    case turing::TapeMovement::RIGHT:
      ++head_;
      if (head_ >= tape_.size()) {
        tape_ += blank_symbol_;
      }
      break;
    case turing::TapeMovement::STOP:
      break;
    default:
    break;
  }
}

}