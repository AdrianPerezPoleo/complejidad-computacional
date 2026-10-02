/**
 * @file automaton_error.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief File containing the possible errors to be thrown when working with a pushdown automaton.
 * @version 1.0
 * @date 29-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AUTOMATON_ERROR
#define AUTOMATON_ERROR

#include <exception>
#include <string>

namespace pda {

/** @brief Base exception for pushdown automaton errors. */
class AutomatonError : public std::exception {
 public:
  explicit AutomatonError(std::string message) : message_{std::move(message)} {}

  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

/** @brief Reports an error while opening or reading a configuration file. */
class ConfigurationFileError : public AutomatonError {
 public:
  using AutomatonError::AutomatonError;
};

/** @brief Reports invalid or inconsistent automaton configuration data. */
class InvalidConfigurationError : public AutomatonError {
 public:
  using AutomatonError::AutomatonError;
};

/** @brief Reports an invalid symbol alphabet definition. */
class InvalidAlphabetError : public AutomatonError {
 public:
  using AutomatonError::AutomatonError;
};

/** @brief Reports a malformed or invalid transition definition. */
class InvalidTransitionError : public AutomatonError {
 public:
  using AutomatonError::AutomatonError;
};

/** @brief Reports input that contains symbols outside the tape alphabet. */
class InvalidInputError : public AutomatonError {
 public:
  using AutomatonError::AutomatonError;
};

}

#endif