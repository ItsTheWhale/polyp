#include "commands.hpp"
#include "packagejson.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::string;

void commands::init() {
  // Does package.json exist?
  std::ifstream packageJsonFile("package.json");
  if (packageJsonFile.good()) {
    char regenerate = 'n';
    do {
      // Regenerate the package.json?
      std::cout << "Package.json already exists. Regenerate? (y/n): ";
      std::cin.get(regenerate);
      if (regenerate != '\n')
        std::cout << '\n';
    } while (!std::cin.fail() && regenerate != 'y' && regenerate != 'n' &&
             regenerate != '\n');
    if (regenerate == 'n')
      return;
  }
  packageJsonFile.close();

  // The JSON itself
  rapidjson::Document DOM;
  DOM.SetObject();

  // Get input
  /// name
  string name = "";
  bool isValidName = false;
  do {
    std::cout << "Package name (default): ";
    std::getline(std::cin, name);
    if (name == "") {
      name = "default";
      break;
    }
    isValidName = packageJson::validate::name(name);
    if (!isValidName)
      std::cout
          << "Name \"" << name
          << "\" is not valid. It must follow rules as defined in "
             "https://docs.npmjs.com/cli/v9/configuring-npm/package-json#name."
          << '\n';
  } while (!isValidName);
  rapidjson::Value nameValue;
  char nameBuffer[214];
  int nameLen = sprintf(nameBuffer, name.c_str());
  nameValue.SetString(nameBuffer, nameLen, DOM.GetAllocator());
  memset(nameBuffer, 0, sizeof(nameBuffer));
  DOM.AddMember("name", nameValue, DOM.GetAllocator());

  // version
  string version = "";
  bool isValidVersion = false;
  do {
    std::cout << "Version (0.0.0): ";
    std::getline(std::cin, version);
    if (version == "") {
      version = "0.0.0";
      break;
    }
    isValidVersion = packageJson::validate::semver(version);
    if (!isValidVersion)
      std::cout << "Version \"" << version
                << "\" is not valid. It must be semantically versioned, as "
                   "specified by "
                   "https://docs.npmjs.com/cli/v9/configuring-npm/"
                   "package-json#version."
                << '\n';
  } while (!isValidVersion);
  rapidjson::Value versionValue;
  char versionBuffer[25];
  int versionLen = sprintf(versionBuffer, version.c_str());
  versionValue.SetString(versionBuffer, versionLen, DOM.GetAllocator());
  memset(versionBuffer, 0, sizeof(versionBuffer));
  DOM.AddMember("version", versionValue, DOM.GetAllocator());

  // description
  string description = "";
  std::cout << "Description: ";
  std::getline(std::cin, description);
  rapidjson::Value descriptionValue;
  char descriptionBuffer[300];
  int descriptionLen = sprintf(descriptionBuffer, description.c_str());
  descriptionValue.SetString(descriptionBuffer, descriptionLen,
                             DOM.GetAllocator());
  memset(descriptionBuffer, 0, sizeof(descriptionBuffer));
  DOM.AddMember("description", descriptionValue, DOM.GetAllocator());

  // entry point
  string entry = "";
  std::cout << "Entry Script: ";
  std::getline(std::cin, entry);
  rapidjson::Value entryValue;
  char entryBuffer[50];
  int entryLen = sprintf(entryBuffer, entry.c_str());
  entryValue.SetString(entryBuffer, entryLen, DOM.GetAllocator());
  memset(entryBuffer, 0, sizeof(entryBuffer));
  DOM.AddMember("entry", entryValue, DOM.GetAllocator());

  // repository
  string repository = "";
  std::cout << "Repository: ";
  std::getline(std::cin, repository);
  rapidjson::Value repositoryValue;
  char repositoryBuffer[100];
  int repositoryLen = sprintf(repositoryBuffer, repository.c_str());
  repositoryValue.SetString(repositoryBuffer, repositoryLen,
                            DOM.GetAllocator());
  memset(repositoryBuffer, 0, sizeof(repositoryBuffer));
  DOM.AddMember("repository", repositoryValue, DOM.GetAllocator());

  // keywords
  string keywordInput = "";
  std::cout << "Keywords: ";
  std::getline(std::cin, keywordInput);
  rapidjson::Value keywords(rapidjson::kArrayType);
  rapidjson::Document::AllocatorType &keywordAllocator = DOM.GetAllocator();
  std::stringstream keywordStream(keywordInput);
  std::string line;
  while (std::getline(keywordStream, line)) {
    std::size_t prev = 0, pos;
    while ((pos = line.find_first_of(" ,", prev)) != std::string::npos) {
      if (pos > prev) {
        rapidjson::Value keyword;
        char keywordBuffer[20];
        int keywordLen =
            sprintf(keywordBuffer, line.substr(prev, pos - prev).c_str());
        keyword.SetString(keywordBuffer, keywordLen, DOM.GetAllocator());
        memset(keywordBuffer, 0, sizeof(keywordBuffer));
        keywords.PushBack(keyword, keywordAllocator);
      }
      prev = pos + 1;
    }
    if (prev < line.length()) {
      rapidjson::Value keyword;
      char keywordBuffer[20];
      int keywordLen =
          sprintf(keywordBuffer, line.substr(prev, std::string::npos).c_str());
      keyword.SetString(keywordBuffer, keywordLen, DOM.GetAllocator());
      memset(keywordBuffer, 0, sizeof(keywordBuffer));
      keywords.PushBack(keyword, keywordAllocator);
    }
  }
  DOM.AddMember("keywords", keywords, DOM.GetAllocator());

  // author
  string author = "";
  std::cout << "Author: ";
  std::getline(std::cin, author);
  rapidjson::Value authorValue;
  char authorBuffer[50];
  int authorLen = sprintf(authorBuffer, author.c_str());
  authorValue.SetString(authorBuffer, authorLen, DOM.GetAllocator());
  memset(authorBuffer, 0, sizeof(authorBuffer));
  DOM.AddMember("author", authorValue, DOM.GetAllocator());

  // license
  string license = "";
  bool isValidLicense = false;
  do {
    std::cout << "License (MIT): ";
    std::getline(std::cin, license);
    if (license == "") {
      license = "MIT";
      break;
    }
    isValidLicense = packageJson::validate::license(license);
    if (!isValidLicense)
      std::cout << "License \"" << license
                << "\" is not valid. It must be a SPDX license identifier, as "
                   "defined in "
                   "https://docs.npmjs.com/cli/v9/configuring-npm/"
                   "package-json#license."
                << '\n';
  } while (!isValidLicense);
  rapidjson::Value licenseValue;
  char licenseBuffer[50];
  int licenseLen = sprintf(licenseBuffer, license.c_str());
  licenseValue.SetString(licenseBuffer, licenseLen, DOM.GetAllocator());
  memset(licenseBuffer, 0, sizeof(licenseBuffer));
  DOM.AddMember("license", licenseValue, DOM.GetAllocator());

  // export
  rapidjson::StringBuffer jsonBuffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
  DOM.Accept(jsonWriter);

  std::cout << '\n' << "Output" << '\n';
  std::cout << jsonBuffer.GetString() << "\n\n";

  char okay = 'n';
  do {
    // Regenerate the package.json?
    std::cout << "Is this okay? (y/n): ";
    std::cin.get(okay);
  } while (!std::cin.fail() && okay != 'y' && okay != 'n' && okay != '\n');
  if (okay == 'n')
    return;
  std::ofstream file;
  file.open("package.json", std::ofstream::out | std::ofstream::trunc);
  file << jsonBuffer.GetString();
  file.close();
}