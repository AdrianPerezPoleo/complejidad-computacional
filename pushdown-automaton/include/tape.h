/**
 * @file tape.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that models a tape containing a string with symbols of a given alphabet.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TAPE_H
#define TAPE_H

#include <iostream>
#include <string>
#include <vector>
#include "alphabet.h"

class Tape {
 public:
  Tape(const Alphabet& tape_alphabet) : alphabet_{tape_alphabet}, head_{0} { }
  Tape(const Tape&) = default;

  void IntroduceString(const std::string& new_string);

  Symbol GetNextSymbol() const;
  void Advance() { ++head_; }
  void Restart() { head_ = 0; tape_ = ""; }
  bool HasSymbolsToRead() const  { return head_ < this->tape_.size(); }

  std::ostream& PrintSymbolsLeft(std::ostream& os) const {
    std::string symbols_left = "";
    for (size_t i{head_}; i < tape_.size(); ++i) {
      symbols_left += tape_[i];
    }
    if (symbols_left == "") symbols_left = "-";
    os << symbols_left;
    return os;
  }

 private:
  std::string tape_;
  size_t head_;
  Alphabet alphabet_;

  bool IsValid(const std::string& tape) const;
  static constexpr Symbol kEmptySymbol = '.';
};

#endif