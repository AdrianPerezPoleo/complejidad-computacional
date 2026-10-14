/**
 * @file tape.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that models a tape containing a string with symbols of a given alphabet.
 * @version 1.0
 * @date 2026-10-14
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
#include "types.h"

namespace turing {

enum TapeMovements {
  RIGHT, LEFT, STOP
};
  
class Tape {
 public:
  Tape(const Alphabet& input_alphabet) : alphabet_{input_alphabet}, head_{0} { }
  Tape(const Tape&) = default;

  bool IntroduceString(const std::string& new_string);

  Symbol Read() const;
  void Write(const Symbol& symbol);
  void Move(const TapeMovements& movement);
  void Restart() { head_ = 0; tape_ = ""; }
  bool HasSymbolsToRead() const  { return head_ < this->tape_.size(); }

  std::ostream& PrintTape(std::ostream& os) const;

 private:
  Symbols tape_;
  int head_;
  Alphabet alphabet_;

  bool IsValid(const std::string& tape) const;
};

}

#endif