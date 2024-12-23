#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class RuntimeError : public runtime_error
{
public:
    RuntimeError(const string &message, const string &func);
};
