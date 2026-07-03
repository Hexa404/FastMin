#pragma once

#include "../managers/ConfigManager.h"
#include "../managers/DeviceManager.h"
#include "../managers/WifiManager.h"
#include "../managers/MqttManager.h"
#include "../managers/DisplayManager.h"

namespace fastmin {

/**
 * @class CoreManager
 * @brief Coordinates general system state and modules.
 * 
 * Implemented as a Singleton to strictly comply with the rule of avoiding 
 * global variables. All hardware and systems will be initialized and accessed 
 * through managers coordinated here.
 */
class CoreManager {
public:
    /**
     * @brief Retrieve the singleton instance of CoreManager.
     * @return CoreManager& Reference to the static instance.
     */
    static CoreManager& getInstance();

    /**
     * @brief Initializes core systems.
     * @return true if successful, false otherwise.
     */
    bool init();

    /**
     * @brief Main update loop to process tasks.
     * Guaranteed to have no delay() calls.
     */
    void update();

    /**
     * @brief Access the Configuration Manager instance.
     * @return ConfigManager& Reference to the config manager.
     */
    ConfigManager& getConfig();

    /**
     * @brief Access the Device Manager instance.
     * @return DeviceManager& Reference to the device manager.
     */
    DeviceManager& getDeviceManager();

    /**
     * @brief Access the WiFi Manager instance.
     * @return WifiManager& Reference to the WiFi manager.
     */
    WifiManager& getWifi();

    /**
     * @brief Access the MQTT Manager instance.
     * @return MqttManager& Reference to the MQTT manager.
     */
    MqttManager& getMqtt();

    /**
     * @brief Access the Display Manager instance.
     * @return DisplayManager& Reference to the display manager.
     */
    DisplayManager& getDisplay();

private:
    ConfigManager _configManager;
    DeviceManager _deviceManager;
    WifiManager _wifiManager;
    MqttManager _mqttManager;
    DisplayManager _displayManager;

    // Private constructors & operators to enforce singleton behavior
    CoreManager() = default;
    ~CoreManager() = default;
    CoreManager(const CoreManager&) = delete;
    CoreManager& operator=(const CoreManager&) = delete;
};

} // namespace fastmin


