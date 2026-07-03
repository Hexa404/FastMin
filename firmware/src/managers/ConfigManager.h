#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <type_traits>

namespace fastmin {

/**
 * @class ConfigManager
 * @brief Manages project configuration values in RAM.
 * 
 * ConfigManager provides type-safe storage and retrieval of configurations
 * using std::variant and templates. It uses std::unordered_map internally
 * for optimal O(1) lookup times.
 */
class ConfigManager {
public:
    // Supported configuration value types
    using ConfigValue = std::variant<bool, int, float, double, std::string>;

    ConfigManager() = default;
    ~ConfigManager() = default;

    /**
     * @brief Set a configuration value.
     * 
     * @tparam T The value type.
     * @param key The configuration key string.
     * @param value The value to associate with the key.
     */
    template <typename T>
    void set(const std::string& key, const T& value) {
        if constexpr (std::is_same_v<T, const char*>) {
            _configMap[key] = std::string(value);
        } else {
            _configMap[key] = value;
        }
    }

    /**
     * @brief Retrieve a configuration value.
     * 
     * @tparam T The value type to retrieve.
     * @param key The configuration key string.
     * @param defaultValue The fallback value if key doesn't exist or types mismatch.
     * @return T The configuration value, or defaultValue.
     */
    template <typename T>
    T get(const std::string& key, const T& defaultValue = T()) const {
        auto it = _configMap.find(key);
        if (it != _configMap.end()) {
            if (const auto* val = std::get_if<T>(&it->second)) {
                return *val;
            }
        }
        return defaultValue;
    }

    /**
     * @brief Check if a key exists in configuration storage.
     * @param key The key string to look up.
     * @return true if key exists, false otherwise.
     */
    bool exists(const std::string& key) const;

    /**
     * @brief Remove a configuration key and its value.
     * @param key The key string to delete.
     * @return true if the key existed and was removed, false otherwise.
     */
    bool remove(const std::string& key);

    /**
     * @brief Clear all stored configuration values.
     */
    void clear();

    /**
     * @brief Get a list of all stored configuration keys.
     * @return std::vector<std::string> The list of keys.
     */
    std::vector<std::string> keys() const;

    /**
     * @brief Get the total number of configurations currently stored.
     * @return size_t Number of elements.
     */
    size_t size() const;

private:
    std::unordered_map<std::string, ConfigValue> _configMap;
};

} // namespace fastmin
