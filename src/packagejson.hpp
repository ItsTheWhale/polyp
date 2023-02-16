#include <string>

using std::string;

#ifndef PACKAGEJSON_HPP_
#define PACKAGEJSON_HPP_

namespace packageJson {
namespace validate {
bool name(string name);
bool semver(string version);
bool license(string license);
} // namespace validate
} // namespace packageJson

#endif