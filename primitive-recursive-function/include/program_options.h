/**
 * @file program_options.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Struct containing the options allowed by the program.
 * @version 1.0
 * @date 27-09-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PROGRAM_OPTIONS
#define PROGRAM_OPTIONS

#include <string>

struct ProgramOptions {
  int base;
  int exponent;
};

ProgramOptions ProcessParameters(const int argc, char* argv[]);

#endif