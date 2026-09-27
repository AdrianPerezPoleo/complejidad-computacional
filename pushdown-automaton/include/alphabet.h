/**
 * @file alphabet.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that contains a set of symbols that belong to an alphabet.
 * @version 1.0
 * @date 24-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ALPHABET_H
#define ALPHABET_H

#include <set>

using Symbol = char;

class Alphabet {
 public:
  Alphabet(const std::set<Symbol>& alphabet) : alphabet_{alphabet} {
    if (alphabet_.count(this->kEmptySymbol) > 0) {
      throw std::invalid_argument("Error en el alfabeto: El símbolo " + kEmptySymbol + std::string(" no puede formar parte de un alfabeto."));
    }
   }

  bool ContainsSymbol(const Symbol& symbol) const { return this->alphabet_.find(symbol) != this->alphabet_.end(); }
 private:
  std::set<Symbol> alphabet_;
  static constexpr Symbol kEmptySymbol = '.';
};

#endif