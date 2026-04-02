#include "../include/io.h"
#include "../include/yaml.h"
#include <format>
#include <sstream>
#include <algorithm>
#include <stdexcept>

// создать отдельно 4 функцию с veiw для всех сотальных использовать для to_yaml

Yaml to_yaml(std::string_view str_view) {
    if (str_view.empty())
        throw std::invalid_argument("YAML is empty");

    Yaml result{};
    bool has_name = false;
    bool has_inn = false;
    bool has_workers = false;

    std::string temp_str(str_view);
    std::istringstream iss(temp_str);
    std::string line;

    while (std::getline(iss, line)) {
        if (line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }

        size_t first_char = line.find_first_not_of(" \t");
        if (first_char != std::string::npos) {
            line = line.substr(first_char);
        }

        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, colon_pos);

        key.erase(key.find_last_not_of(" \t") + 1);

        std::string value = line.substr(colon_pos + 1);

        size_t value_start = value.find_first_not_of(" \t");
        if (value_start != std::string::npos) {
            value = value.substr(value_start);
        }
        value.erase(value.find_last_not_of(" \t") + 1);

        if (key == "name") {
            result.name = value;
            has_name = true;
        } else if (key == "inn") {

            if (value.size() != 10) {
                throw std::invalid_argument("INN must be exactly 10 characters");
            }
            for (char c : value) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    throw std::invalid_argument("INN must contain only digits");
                }
            }
            std::copy(value.begin(), value.end(), result.inn);
            result.inn[10] = '\0';
            has_inn = true;
        } else if (key == "workers") {
            try {
                int workers = std::stoi(value);
                if (workers < 0) {
                    throw std::invalid_argument("Workers count cannot be negative");
                }
                result.workers = workers;
                has_workers = true;
            } catch (const std::exception&) {
                throw std::invalid_argument("Invalid workers count: must be a non-negative integer");
            }
        }
    }

    if (!has_name) {
        throw std::invalid_argument("Missing required field: name");
    }
    if (!has_inn) {
        throw std::invalid_argument("Missing required field: inn");
    }
    if (!has_workers) {
        throw std::invalid_argument("Missing required field: workers");
    }

    return result;
}

Yaml to_yaml(const std::string& str) {
    return to_yaml(std::string_view(str));
}

Yaml to_yaml(const char *str){
    if (str == nullptr)
        throw std::invalid_argument("string is null");
    std::string sstr(str);
    return to_yaml(std::string_view(sstr));
}

Yaml to_yaml(const char* str, size_t size) {
    if (str == nullptr)
        throw std::invalid_argument("string is null");
    std::string sstr(str, size);
    return to_yaml(std::string_view(sstr));
}

std::string from_yaml(const Yaml& yaml, const std::string& name) {
    return std::format("{}:\n  name: {}\n  inn: {}\n  workers: {}\n",
                      name, yaml.name, yaml.inn, yaml.workers);
}

char* from_yaml(const Yaml& yaml, const char* name) {
    if (name == nullptr)
        throw std::invalid_argument("string is null");
    std::string str(name);
    std::string ans = from_yaml(yaml, str);
    char *result = new char[ans.size() + 1];
    std::copy(ans.begin(), ans.end(), result);
    result[ans.size()] = '\0';
    return result;
}

char* from_yaml(const Yaml& yaml, const char* name , size_t size) {
    if (name == nullptr)
        throw std::invalid_argument("string is null");
    std::string str(name, size);
    std::string ans = from_yaml(yaml, str);
    char *result = new char[ans.size() + 1];
    std::copy(ans.begin(), ans.end(), result);
    result[ans.size()] = '\0';
    return result;
}