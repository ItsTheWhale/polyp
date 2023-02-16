#include "CLI11/CLI11.hpp"
#include "polyp.hpp"
#include "packagejson.hpp"
#include "commands.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <iostream>


int main(int argc, char **argv) {
  // Create CLI app
  CLI::App app{"A simple and fast JavaScript package manager"};
  app.require_subcommand(1, 1);

  // init command
  CLI::App *sub = app.add_subcommand("init", "Initialise a new package.json")
                      ->callback(commands::init);

  CLI11_PARSE(app, argc, argv);
}