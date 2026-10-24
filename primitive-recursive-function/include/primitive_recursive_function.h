/**
 * @file primitive_recursive_function.h
 * @author Adrián Pérez Poleo (alu0101635224@ull.edu.es)
 * @brief Definition of the Primitive Recurse Function class.
 * @version 1.0
 * @date 2026-10-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PRIMITIVE_RECURSIVE_FUNCTION
#define PRIMITIVE_RECURSIVE_FUNCTION

class PrimitiveRecursiveFunction {
 public:
  virtual ~PrimitiveRecursiveFunction() = default;

  static unsigned long GetCallCount() { return call_count_; }
  static void ResetCallCount() { call_count_ = 0; }
 protected:
  static unsigned long call_count_;
  void AddFunctionCall() const { ++call_count_; }
};

#endif