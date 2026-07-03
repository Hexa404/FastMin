#pragma once

#include "../models/DeviceInfo.h"
#include <cstring>
#include <unordered_map>
#include <vector>

namespace fastmin {

/**
 * @class DeviceManager
 * @brief Manages the in‑memory registry of DeviceInfo objects.
 */
class DeviceManager {
public:
    // Register a new device (or replace existing by id). Returns false if id empty.
    bool registerDevice(const DeviceInfo& device);

    // Unregister a device by its id. Returns true if it existed.
    bool unregisterDevice(const std::string& id);

    // Retrieve a pointer to a device; nullptr if not found.
    const DeviceInfo* find(const std::string& id) const;
    DeviceInfo* find(const std::string& id);

    // Does a device with this id exist?
    bool exists(const std::string& id) const;

    // List all registered devices.
    std::vector<DeviceInfo> list() const;

    // Number of registered devices.
    size_t count() const;

    // Remove all devices.
    void clear();

private:
    std::unordered_map<std::string, DeviceInfo> _devices;
};

} // namespace fastmin
