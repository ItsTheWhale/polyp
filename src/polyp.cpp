#include "CLI11/CLI11.hpp"
#include "commands.hpp"
#include "packagejson.hpp"
#include "polyp.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  // Create CLI app
  CLI::App app{"A simple and fast JavaScript package manager"};
  app.require_subcommand(1, 1);

  // Options
  cliOptionsStruct cliOptions;

  // init command
  CLI::App *initCommand =
      app.add_subcommand("init", "Initialise a new package.json")
          ->callback([&cliOptions] { commands::init(&cliOptions); });
  initCommand->add_flag("-y, --yes", cliOptions.yes,
                        "Automatically fill out default fields");

  // run command
  CLI::App *runCommand =
      app.add_subcommand("run", "Runs a script")->callback([&cliOptions] {
        commands::run(&cliOptions);
      });
  runCommand->add_option("name", cliOptions.target, "Script name to be runned")
      ->required();

  CLI11_PARSE(app, argc, argv);
}