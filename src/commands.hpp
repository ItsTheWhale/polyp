#include "polyp.hpp"
#include <string>

using std::string;

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

namespace commands {
void init(cliOptionsStruct* cliOptions);
void run(cliOptionsStruct* cliOptions);
}

#endif