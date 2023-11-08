#include "kv_store.h"
#include <iostream>
#include <sstream>

int main() {
    KeyValueStore kv_store;
    std::string command, key, value;

    while (true) {
        std::cout << "Enter a command (set/get/delete/update/log/quit): ";
        std::cin >> command;

        if (command == "set") {
            std::cin >> key >> value;
            int result = kv_store.set(key, value);
            if (result == 0) {
                std::cout << "Key-Value pair set." << std::endl;
            } else {
                std::cout << "Failed to set Key-Value pair." << std::endl;
            }
        } else if (command == "get") {
            std::cin >> key;
            std::string result;
            int getStatus = kv_store.get(key, result);
            if (getStatus == 0) {
                std::cout << "Value: " << result << std::endl;
            } else {
                std::cout << "Failed to get the value." << std::endl;
            }
        } else if (command == "delete") {
            std::cin >> key;
            int result = kv_store.del(key);
            if (result == 0) {
                std::cout << "Key deleted." << std::endl;
            } else {
                std::cout << "Failed to delete the key." << std::endl;
            }
        } else if (command == "update") {
            std::cin >> key >> value;
            int result = kv_store.update(key, value);
            if (result == 0) {
                std::cout << "Key updated." << std::endl;
            } else {
                std::cout << "Failed to update the key." << std::endl;
            }
        } else if (command == "log") {
            std::vector<std::string> log = kv_store.get_log();
            if (log.empty()) {
                std::cout << "Command log is empty." << std::endl;
            } else {
                std::cout << "Command log:" << std::endl;
                for (const std::string& entry : log) {
                    std::cout << entry << std::endl;
                }
            }
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}