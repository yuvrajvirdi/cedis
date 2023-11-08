#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <string>
#include <vector>
#include <map>

class KeyValueStore {
public:
    KeyValueStore();

    int set(const std::string& key, const std::string& value);
    int get(const std::string& key, std::string& result);
    int del(const std::string& key);
    int update(const std::string& key, const std::string& new_value);
    std::vector<std::string> get_log();

private:
    std::map<std::string, std::string> data;
    std::vector<std::string> log;

    std::string get_current_time();
};

#endif