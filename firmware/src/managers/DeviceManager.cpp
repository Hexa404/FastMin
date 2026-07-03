#include "DeviceManager.h"

namespace fastmin {

std::string deviceTypeToString(DeviceType type) {
    switch (type) {
        case DeviceType::DS18B20:     return "DS18B20";
        case DeviceType::DHT22:       return "DHT22";
        case DeviceType::RELAY:       return "RELAY";
        case DeviceType::LED:         return "LED";
        case DeviceType::BUTTON:      return "BUTTON";
        case DeviceType::SERVO:       return "SERVO";
        case DeviceType::PUMP:        return "PUMP";
        case DeviceType::ULTRASONIC:  return "ULTRASONIC";
        case DeviceType::TURBIDITY:   return "TURBIDITY";
        case DeviceType::FLOW_SENSOR: return "FLOW_SENSOR";
        case DeviceType::UNKNOWN:
        default:                      return "UNKNOWN";
    }
}

DeviceType stringToDeviceType(const std::string& typeStr) {
    if (typeStr == "DS18B20")     return DeviceType::DS18B20;
    if (typeStr == "DHT22")       return DeviceType::DHT22;
    if (typeStr == "RELAY")       return DeviceType::RELAY;
    if (typeStr == "LED")         return DeviceType::LED;
    if (typeStr == "BUTTON")      return DeviceType::BUTTON;
    if (typeStr == "SERVO")       return DeviceType::SERVO;
    if (typeStr == "PUMP")        return DeviceType::PUMP;
    if (typeStr == "ULTRASONIC")  return DeviceType::ULTRASONIC;
    if (typeStr == "TURBIDITY")   return DeviceType::TURBIDITY;
    if (typeStr == "FLOW_SENSOR") return DeviceType::FLOW_SENSOR;
    return DeviceType::UNKNOWN;
}

bool DeviceManager::registerDevice(const DeviceInfo& device) {
    if (device.id.empty()) {
        return false;
    }
    if (_devices.find(device.id) != _devices.end()) {
        return false; // Already registered
    }
    _devices[device.id] = device;
    return true;
}

bool DeviceManager::unregisterDevice(const std::string& id) {
    return _devices.erase(id) > 0;
}

const DeviceInfo* DeviceManager::find(const std::string& id) const {
    auto it = _devices.find(id);
    if (it != _devices.end()) {
        return &it->second;
    }
    return nullptr;
}

bool DeviceManager::exists(const std::string& id) const {
    return _devices.find(id) != _devices.end();
}

std::vector<DeviceInfo> DeviceManager::list() const {
    std::vector<DeviceInfo> result;
    result.reserve(_devices.size());
    for (const auto& entry : _devices) {
        result.push_back(entry.second);
    }
    return result;
}

size_t DeviceManager::count() const {
    return _devices.size();
}

void DeviceManager::clear() {
    _devices.clear();
}

} // namespace fastmin
