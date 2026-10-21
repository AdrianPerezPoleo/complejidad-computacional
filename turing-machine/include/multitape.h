/**
 * @file multitape.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that implements a multitape.
 * @version 1.0
 * @date 2026-10-16
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef MULTITAPE_H
#define MULTITAPE_H

#include "tape.h"

#include <vector>

namespace turing {

class Multitape {
 public:
  Multitape(int number_of_tapes, const Alphabet& alphabet, const Symbol& blank_symbol) {
    for (int i{0}; i < number_of_tapes; ++i) {
      multitape_.emplace_back(alphabet, blank_symbol);
    }
  }

  void Move(const std::vector<Movement>&);
  Symbols GetCurrentSymbols() const;
  void InsertString(const std::string& new_string) { multitape_[0].IntroduceString(new_string); }
  void Restart();
  void PrintTapes(std::ostream&) const;

 private:
  std::vector<Tape> multitape_;
};


}

#endif