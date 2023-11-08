#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "kv_store.h"

KeyValueStore::KeyValueStore() {}

/**
 * @brief Gets current time
 * @return Current time
 */
std::string KeyValueStore::get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);
    
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

/**
 * @brief Sets key value pair
 * @param key The key
 * @param value The value to be mapped to the key
 * @return 0 for success, 1 for failure
 */
int KeyValueStore::set(const std::string& key, const std::string& value) {
    data[key] = value;
    log.push_back(get_current_time() + " - SET(" + key + ", " + value + ")");
    return 0;
}

/**
 * @brief Gets the value associated with a key
 * @param key The key to look up
 * @param result The value if found
 * @return 0 for success, 1 for failure
 */
int KeyValueStore::get(const std::string& key, std::string& result) {
    if (data.find(key) != data.end()) {
        result = data[key];
        log.push_back(get_current_time() + " - GET(" + key + ")");
        return 0;
    }
    log.push_back(get_current_time() + " - GET(" + key + ") - FAILURE(Key not found)");
    return 1;
}

/**
 * @brief Removes a key from the key-value store
 * @param key The key to remove
 * @return 0 for success, 1 for failure
 */
int KeyValueStore::del(const std::string& key) {
    if (data.find(key) != data.end()) {
        data.erase(key);
        log.push_back(get_current_time() + " - DELETE(" + key + ")");
        return 0;
    }
    log.push_back(get_current_time() + " - DELETE(" + key + ") - FAILURE(Key not found)");
    return 1;
}

/**
 * @brief Updates a key with a new value
 * @param key The key to update
 * @param value The new value
 * @return 0 for success, 1 for failure
 */
int KeyValueStore::update(const std::string& key, const std::string& value) {
    if (data.find(key) != data.end()) {
        data[key] = value;
        log.push_back(get_current_time() + " - UPDATE(" + key + ", " + value + ")");
        return 0; // Success
    }
    log.push_back(get_current_time() + " - UPDATE(" + key + ", " + value + ") - FAILURE(Key not found)");
    return 1; // Failure
}

/**
 * @brief Gets past activity log
 * @return log
 */
std::vector<std::string> KeyValueStore::get_log() {
    return log;
}