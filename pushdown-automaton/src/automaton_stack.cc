/**
 * @file automaton_stack.cc
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Implementation of the automaton stack class.
 * @version 1.0
 * @date 01-10-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../include/automaton_stack.h"

/**
 * @brief Stores a new symbol into the top of the stack.
 * 
 * @param symbol Symbol to push into the stack.
 */
void AutomatonStack::Push(const Symbol& symbol) {
  if (this->alphabet_.ContainsSymbol(symbol)) {
    stack_.push_back(symbol);
  } else {
    throw InvalidInputError("El símbolo que se ha intentado introducir en la pila: " + std::to_string(symbol) + "no pertenece al alfabeto.");
  }  
}

/**
 * @brief Inserts a group of symbols into the stack.
 * 
 * @param symbols Symbols to be introduced.
 */
void AutomatonStack::Push(const Symbols& symbols) {
  Symbols reversed_symbols = symbols;
  std::reverse(reversed_symbols.begin(), reversed_symbols.end());
  for (const auto& symbol : reversed_symbols) {
    if (symbol == kEmptySymbol) 
      break;
    this->Push(symbol);
  }
}

/**
 * @brief Displays the content of the stack from top to bottom.
 * 
 * @param os Stream where the symbols will be placed.
 * @return std::ostream& 
 */
std::ostream& AutomatonStack::PrintContent(std::ostream& os) const {
  std::string stack_content = "";
  for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) {
    stack_content += *it;
  }
  if (stack_content == "") stack_content = "-";
  os << stack_content;
  return os; 
}