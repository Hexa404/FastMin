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
WifiManager& CoreManager::getWifi() {
    return _wifiManager;
}
MqttManager& CoreManager::getMqtt() {
    return _mqttManager;
}
DisplayManager& CoreManager::getDisplay() {
    return _displayManager;
}


bool CoreManager::init() {
    Serial.begin(115200);
    Serial.println("FastMin CoreManager initializing...");

    // Initialize display first so we can show boot/status messages
    _displayManager.init();
    _displayManager.setState(DisplayState::BOOT);
    _displayManager.update();

    // Seed default configurations if not present
    if (!_configManager.exists("wifi_ssid")) {
        _configManager.set<std::string>("wifi_ssid", "UTY-Network");
    }
    if (!_configManager.exists("wifi_password")) {
        _configManager.set<std::string>("wifi_password", "Semangat99@UTY");
    }
    if (!_configManager.exists("mqtt_broker")) {
        _configManager.set<std::string>("mqtt_broker", "broker.hivemq.com");
    }
    if (!_configManager.exists("mqtt_port")) {
        _configManager.set<int>("mqtt_port", 1883);
    }

    // Initialize network managers
    _wifiManager.init();
    _mqttManager.init();

    // Verification handler for Milestone 2 MQTT subscription
    _mqttManager.subscribe("fastmin/test/control", [](const std::string& topic, const std::string& payload) {
        Serial.print("Test Handler received [");
        Serial.print(topic.c_str());
        Serial.print("]: ");
        Serial.println(payload.c_str());

        // Make the face react and animate talking with the received text response
        CoreManager::getInstance().getDisplay().showTalkingMessage(payload);
    });

    Serial.println("FastMin CoreManager initialized.");
    return true;
}

void CoreManager::update() {
    _wifiManager.update();
    _mqttManager.update();

    // Coordinate screen state based on Wifi and MQTT connection status
    if (!_wifiManager.isConnected()) {
        if (_wifiManager.getState() == WifiState::CONNECTING) {
            _displayManager.setState(DisplayState::WIFI_CONNECTING);
        } else {
            _displayManager.showMessage("WiFi Disconnected", "Status: Reconnecting", "");
        }
    } else {
        // WiFi is connected
        if (!_mqttManager.isConnected()) {
            char ipBuf[32];
            snprintf(ipBuf, sizeof(ipBuf), "IP: %s", WiFi.localIP().toString().c_str());
            _displayManager.showMessage("WiFi Connected", ipBuf, "Connecting MQTT...");
        } else {
            // Both are connected. Show animated robot face!
            // Do not force FACE_IDLE if currently in FACE_TALKING state
            if (_displayManager.getState() != DisplayState::FACE_TALKING && 
                _displayManager.getState() != DisplayState::FACE_IDLE) {
                _displayManager.setState(DisplayState::FACE_IDLE);
            }
        }
    }

    _displayManager.update();
}

} // namespace fastmin

