#include "ConfigManager.h"

namespace fastmin {

bool ConfigManager::exists(const std::string& key) const {
    return _configMap.find(key) != _configMap.end();
}

bool ConfigManager::remove(const std::string& key) {
    return _configMap.erase(key) > 0;
}

void ConfigManager::clear() {
    _configMap.clear();
}

std::vector<std::string> ConfigManager::keys() const {
    std::vector<std::string> allKeys;
    allKeys.reserve(_configMap.size());
    for (const auto& entry : _configMap) {
        allKeys.push_back(entry.first);
    }
    return allKeys;
}

size_t ConfigManager::size() const {
    return _configMap.size();
}

} // namespace fastmin
