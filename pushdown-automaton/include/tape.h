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
  Tape(const std::vector<Symbol> tape, const Alphabet& tape_alphabet);

  Symbol GetNextSymbol();  // Comprobar si hay un símbolo que devolver a continuación o si ya se acabó la lectura
 private:
  std::vector<Symbol> tape_;
  int head_;

  bool IsValid(const std::vector<Symbol>& tape, const Alphabet& alphabet) const;
  static constexpr Symbol kEmptySymbol = '.';
};

#endif