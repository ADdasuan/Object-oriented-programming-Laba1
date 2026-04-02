#ifndef INPUT
#define INPUT

#include <string>
#include <../include/yaml.h>

std::string input_yaml_string_for_parsing();

Yaml input_organization_data();

void validate_inn(const std::string& inn);

int validate_and_parse_workers(const std::string& workers_str);

#endif