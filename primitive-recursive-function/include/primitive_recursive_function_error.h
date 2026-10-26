/**
 * @file primitive_recursive_function_error.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Class that defines the errors that can appear in the Primitive Recursive Function program.
 * @version 1.0
 * @date 26-10-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <string>
#include <exception>

/** @brief Base exception for primitive recursive function errors. */
class PrimitiveRecursiveFunctionError : public std::exception {
 public:
  PrimitiveRecursiveFunctionError(std::string message) : message_{std::move(message)} {}

  const char* what() const noexcept override { return message_.c_str(); }
 private:
  std::string message_;
};

/** @brief Reports an error when a function is used with a wrong arity. */
class WrongArity : public PrimitiveRecursiveFunctionError {
 public:
  WrongArity(const std::string& message) : PrimitiveRecursiveFunctionError(message) { }
};