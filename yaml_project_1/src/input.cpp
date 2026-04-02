#include "../include/input.h"
#include <stdexcept>
#include <../include/yaml.h>
#include <limits>

Yaml input_organization_data() {
    Yaml data;

    std::cout << "Enter organization name: ";
    std::getline(std::cin, data.name);

    if (std::cin.eof()) {
        throw std::runtime_error("Input cancelled by user");
    }

    if (data.name.empty()) {
        throw std::invalid_argument("Organization name cannot be empty");
    }

    std::string inn_input;
    bool correct_inn = false;

    while (!correct_inn) {
        try {
            std::cout << "Enter INN (10 digits): ";
            std::getline(std::cin, inn_input);

            if (std::cin.eof()) {
                throw std::runtime_error("Ok exit ");
            }

            validate_inn(inn_input);

            if (inn_input.size() != 10) {
                throw std::invalid_argument("INN must be exactly 10 characters");
            }

            std::copy(inn_input.begin(), inn_input.end(), data.inn);
            data.inn[10] = '\0';
            correct_inn = true;

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "Please try again to enter\n" << std::endl;
        }
    }

    std::string workers_str;
    bool correct_workers = false;

    while (!correct_workers) {
        try {
            std::cout << "Enter number of workers: ";
            std::getline(std::cin, workers_str);

            if (std::cin.eof()) {
                throw std::runtime_error("Input cancelled by user");
            }

            data.workers = validate_and_parse_workers(workers_str);
            correct_workers = true;

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "Please try again to enter\n" << std::endl;
        }
    }

    return data;
}

std::string input_yaml_string_for_parsing() {
    std::cout << "Enter YAML string (empty line to finish):\n";
    std::cout << "Example format:\n";
    std::cout << "organization:\n";
    std::cout << "  name: MEPhI\n";
    std::cout << "  inn: 7724068140\n";
    std::cout << "  workers: 700\n\n";

    std::string yaml_str;
    std::string line;
//eof обработать надо + bad + fail
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        yaml_str += line + "\n";
    }

    if (std::cin.eof()) {
        throw std::runtime_error("Input cancelled");
    }
    if (std::cin.fail()) {
        throw std::runtime_error("Input failled");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (std::cin.bad()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Fatal error");
    }

    return yaml_str;
}

void validate_inn(const std::string& inn) {
    if (inn.size() != 10) {
        throw std::invalid_argument("INN must be exactly 10 characters");
    }
    for (char c : inn) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("INN must contain only digits");
        }
    }
}

int validate_and_parse_workers(const std::string& workers_str) {
    if (workers_str.empty()) {
        throw std::invalid_argument("Workers count cannot be empty");
    }
    try {
        int workers = std::stoi(workers_str);
        if (workers < 0) {
            throw std::invalid_argument("Workers count cannot be negative");
        }
        return workers;
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid workers count: must be a non-negative integer");
    }
}