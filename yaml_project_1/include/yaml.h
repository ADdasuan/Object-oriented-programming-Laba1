#ifndef IO
#define IO

#include <iostream>
#include <string>

struct Yaml {
    std::string name;
    char inn[11];
    size_t workers;
};

Yaml to_yaml(std::string_view str_view);
Yaml to_yaml(const std::string& str);
Yaml to_yaml(const char *str);
Yaml to_yaml(const char* str, size_t size);

std::string from_yaml(const Yaml& yaml, const std::string& name);
char* from_yaml(const Yaml& yaml, const char* name);
char* from_yaml(const Yaml& yaml, const char* name , size_t size);


#endif