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
#include <unordered_map>
#include <vector>

#include "alphabet.h"
#include "types.h"

namespace turing {

enum class TapeMovement {
  RIGHT, LEFT, STOP
};

struct Movement {
  Symbol next_symbol;
  TapeMovement movement;
};

inline TapeMovement StringToTapeMovement(const std::string& str) {
  static const std::unordered_map<std::string, TapeMovement> movement_map = {
    {"R", TapeMovement::RIGHT},
    {"L", TapeMovement::LEFT},
    {"S", TapeMovement::STOP}
  };

  auto it = movement_map.find(str);
  if (it != movement_map.end()) {
    return it->second;
  }

  throw std::invalid_argument("Movimiento de cinta invalido: " + str);
}
  
class Tape {
 public:
  Tape(const Alphabet& input_alphabet, const Symbol blank_symbol) : alphabet_{input_alphabet}, head_{0}, blank_symbol_{blank_symbol} { }
  Tape(const Tape&) = default;

  bool IntroduceString(const std::string& new_string);

  Symbol Read() const;
  void ExecuteMovement(const Movement& move);
  void Restart() { head_ = 0; tape_ = ""; }
  bool HasSymbolsToRead() const  { return head_ < this->tape_.size(); }

  std::ostream& PrintTape(std::ostream& os) const;

 private:
  Symbols tape_;
  int head_;
  Alphabet alphabet_;
  Symbol blank_symbol_;

  bool IsValid(const std::string& tape) const;
  void Write(const Symbol& symbol);
  void Move(const TapeMovement& movement);
};

}

#endif