#include "error.h"

RuntimeError::RuntimeError(const string &message, const string &func)
    : runtime_error(message + " in function: " + func) {}
