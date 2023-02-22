#include "commands.hpp"
#include "polyp.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <iostream>
#include <string>

using std::string;

void commands::run(cliOptionsStruct *cliOptions) {
  // Is there a target
  if (cliOptions->target == "") {
    std::cerr << "No script name specified" << '\n';
    return;
  }

  // Read package.json
  std::fstream packageJsonFile("package.json");
  if (!packageJsonFile.good()) {
    std::cerr << "Error: Package.json is not found." << '\n';
    packageJsonFile.close();
    return;
  }
  string packageJson = "";
  string readText;
  while (std::getline(packageJsonFile, readText)) {
    packageJson += readText;
  }
  rapidjson::Document DOM;
  DOM.Parse(packageJson.c_str());

  // Is the JSON or script valid?
  if (!DOM.IsObject()) {
    std::cerr << "Error: The package.json could not be parsed" << '\n';
    packageJsonFile.close();
    return;
  }

  if (!DOM["scripts"].IsObject()) {
    std::cerr << "Error: \"Scripts\" key must be an object" << '\n';
    packageJsonFile.close();
    return;
  }

  auto scriptObject = DOM["scripts"].GetObject();

  bool hasScript = false;
  for (rapidjson::Value::ConstMemberIterator itr = scriptObject.MemberBegin();
       itr != scriptObject.MemberEnd(); itr++) {
    if (itr->name.GetString() == cliOptions->target) {
      hasScript = true;
      std::cout << cliOptions->target << "> " << itr->value.GetString() << '\n';
      system(itr->value.GetString());
      break;
    }
  }
  if (!hasScript) {
    std::cerr << "No script of the name " << cliOptions->target << " was found"
              << '\n';
  }

  packageJsonFile.close();
}