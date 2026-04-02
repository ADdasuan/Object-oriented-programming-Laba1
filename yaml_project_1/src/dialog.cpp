
#include <iostream>
#include <limits>
#include <../include/yaml.h>
#include <../include/input.h>

Yaml select_and_parse_yaml_string(const std::string& yaml_input) {
    std::cout << "Choose parsing type:\n";
    std::cout << "1) std::string version - format function\n";
    std::cout << "2) const char* version - format function\n";
    std::cout << "3) const char* + size_t - format function\n";
    std::cout << "Choice: ";

    int choice;
    if (!(std::cin >> choice)) {
        throw std::invalid_argument("Invalid choice input");
    }
    std::cin.ignore();

    switch (choice) {
        case 1:
            return to_yaml(yaml_input);

        case 2:
            return to_yaml(yaml_input.c_str());

        case 3:
            return to_yaml(yaml_input.c_str(), yaml_input.size());

        default:
            throw std::invalid_argument("Invalid choice: " + std::to_string(choice));
    }
}

void handle_parse_yaml_to_data() {
    std::cout << "\n=== Parse YAML String to Organization Data ===\n";

    try {
        std::string yaml_input = input_yaml_string_for_parsing();
        if (yaml_input.empty()) {
            throw std::invalid_argument("YAML string cannot be empty");
        }

        Yaml result = select_and_parse_yaml_string(yaml_input);

        std::cout << "\n=== Parsed Organization Data ===\n";
        std::cout << "Name: " << result.name << "\n";
        std::cout << "INN: " << std::string(result.inn, 10) << "\n";
        std::cout << "Workers: " << result.workers << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

std::string select_and_format_yaml_data(const Yaml& data, const std::string& root_name) {
    std::cout << "Choose conversion type:\n";
    std::cout << "1) std::string version - format function\n";
    std::cout << "2) const char* version - format function\n";
    std::cout << "3) const char* + size_t version formatting\n";
    std::cout << "Choice: ";

    int choice;
    if (!(std::cin >> choice)) {
        throw std::invalid_argument("Invalid argument");
    }
    std::cin.ignore();

    switch (choice) {
        case 1:
            return from_yaml(data, root_name);

        case 2: {
            char* result = from_yaml(data, root_name.c_str());
            if (!result) {
                throw std::runtime_error("Conversion returned null");
            }

            std::string str_result;
            try {
                str_result = result;
            } catch (...) {
                delete[] result;
                throw;
            }
            delete[] result;
            return str_result;
        }

        case 3: {
            char* result = from_yaml(data, root_name.c_str(), root_name.size());
            if (!result) {
                throw std::runtime_error("Conversion returned null");
            }

            std::string str_result(result);
            delete[] result;
            return str_result;
        }

        default:
            throw std::invalid_argument("Invalid choice: " + std::to_string(choice));
    }
}

void handle_convert_data_to_yaml() {
    std::cout << "\n=== Convert Organization Data to YAML String ===\n";

    try {
        Yaml data = input_organization_data();

        std::cout << "Enter root name for YAML: ";
        std::string root_name;
        std::getline(std::cin, root_name);
        if (root_name.empty()) {
            throw std::invalid_argument("Root name cannot be empty");
        }

        std::string yaml_result = select_and_format_yaml_data(data, root_name);
        std::cout << "\n=== YAML Result ===\n";
        std::cout << yaml_result << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void dialog() {
    std::cout << "=== YAML - LABA №1 ===\n";
    while (true) {
        int choice = 0;
        try {
            std::cout << "\nMenu:\n";
            std::cout << "1. Convert data to YAML String\n";
            std::cout << "2. Convert YAML String to data\n";
            std::cout << "Choice function: ";

            std::cin >> choice;
            if (std::cin.eof()) {
                std::cout << "\nExit program" << std::endl;
                break;
            }

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid input");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    handle_convert_data_to_yaml();
                    break;
                case 2:
                    handle_parse_yaml_to_data();
                    break;
                default:
                    throw std::out_of_range("Function " + std::to_string(choice) + " doesn't exist");  // ПРАВКА 3: исправил опечатку
            }

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n\n";

            if (std::cin.fail()) {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}