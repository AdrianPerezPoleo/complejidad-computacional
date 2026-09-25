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

#include <vector>
#include "alphabet.h"

class Tape {
 public:
  Tape(const Alphabet& tape_alphabet) : alphabet_{tape_alphabet} { }

  void IntroduceString(const std::vector<Symbol>& new_string);
  Symbol GetNextSymbol();
 private:
  std::vector<Symbol> tape_;
  int head_;

  Alphabet alphabet_;

  bool IsValid(const std::vector<Symbol>& tape) const;
  static constexpr Symbol kEmptySymbol = '.';
};

#endif