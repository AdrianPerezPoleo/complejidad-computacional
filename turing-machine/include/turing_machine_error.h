/**
 * @file turing_machine_error.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief File containing the possible errors to be thrown when working with a pushdown automaton.
 * @version 1.0
 * @date 29-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TURING_MACHINE_ERROR
#define TURING_MACHINE_ERROR

#include <exception>
#include <string>

namespace tm {

/** @brief Base exception for pushdown automaton errors. */
class TuringMachineError : public std::exception {
 public:
  explicit TuringMachineError(std::string message) : message_{std::move(message)} {}

  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

/** @brief Reports an error while opening or reading a configuration file. */
class ConfigurationFileError : public TuringMachineError {
 public:
  ConfigurationFileError(const std::string& message) : TuringMachineError(message) { }
};

/** @brief Reports invalid or inconsistent automaton configuration data. */
class InvalidConfigurationError : public TuringMachineError {
 public:
  InvalidConfigurationError(const std::string& message) : TuringMachineError(message) { }
};

/** @brief Reports an invalid symbol alphabet definition. */
class InvalidAlphabetError : public TuringMachineError {
 public:
  InvalidAlphabetError(const std::string& message) : TuringMachineError(message) { }
};

/** @brief Reports a malformed or invalid transition definition. */
class InvalidTransitionError : public TuringMachineError {
 public:
  InvalidTransitionError(const std::string& message) : TuringMachineError(message) { }
};

/** @brief Reports input that contains symbols outside the tape alphabet. */
class InvalidInputError : public TuringMachineError {
 public:
  InvalidInputError(const std::string& message) : TuringMachineError(message) { }
};

}

#endif