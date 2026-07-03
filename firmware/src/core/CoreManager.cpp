#include "CoreManager.h"
#include <Arduino.h>

namespace fastmin {

CoreManager& CoreManager::getInstance() {
    static CoreManager instance;
    return instance;
}

ConfigManager& CoreManager::getConfig() {
    return _configManager;
}
DeviceManager& CoreManager::getDeviceManager() {
    return _deviceManager;
}


bool CoreManager::init() {
    Serial.begin(115200);
    Serial.println("FastMin CoreManager initialized.");
    return true;
}

void CoreManager::update() {
    // Initial skeleton loop, logic will be added in subsequent milestones.
}

} // namespace fastmin

