#include "WifiManager.h"
#include "../core/CoreManager.h"
#include <Arduino.h>

namespace fastmin {

bool WifiManager::init() {
    auto& config = CoreManager::getInstance().getConfig();
    _ssid = config.get<std::string>("wifi_ssid", "");
    _password = config.get<std::string>("wifi_password", "");
    
    WiFi.mode(WIFI_STA);
    
    Serial.println("WifiManager initialized.");
    transitionTo(WifiState::DISCONNECTED);
    return true;
}

void WifiManager::transitionTo(WifiState newState) {
    _state = newState;
    _stateTimer = millis();
    
    switch (_state) {
        case WifiState::DISCONNECTED:
            Serial.println("WiFi State: DISCONNECTED");
            break;
        case WifiState::CONNECTING:
            Serial.print("WiFi State: CONNECTING to SSID: ");
            Serial.println(_ssid.c_str());
            break;
        case WifiState::CONNECTED:
            Serial.print("WiFi State: CONNECTED. IP: ");
            Serial.println(WiFi.localIP());
            break;
        case WifiState::WAITING_TO_RECONNECT:
            Serial.println("WiFi State: WAITING_TO_RECONNECT");
            break;
    }
}

void WifiManager::update() {
    // If credentials are loaded dynamically or updated
    if (_ssid.empty()) {
        auto& config = CoreManager::getInstance().getConfig();
        _ssid = config.get<std::string>("wifi_ssid", "");
        _password = config.get<std::string>("wifi_password", "");
        if (_ssid.empty()) {
            return; // No configuration, do nothing
        }
    }

    unsigned long now = millis();

    switch (_state) {
        case WifiState::DISCONNECTED: {
            WiFi.begin(_ssid.c_str(), _password.c_str());
            transitionTo(WifiState::CONNECTING);
            break;
        }
        case WifiState::CONNECTING: {
            if (WiFi.status() == WL_CONNECTED) {
                transitionTo(WifiState::CONNECTED);
            } else if (now - _stateTimer >= _connectionTimeout) {
                Serial.println("WiFi: Connection timeout.");
                WiFi.disconnect();
                transitionTo(WifiState::WAITING_TO_RECONNECT);
            }
            break;
        }
        case WifiState::CONNECTED: {
            if (WiFi.status() != WL_CONNECTED) {
                Serial.println("WiFi: Connection lost.");
                transitionTo(WifiState::WAITING_TO_RECONNECT);
            }
            break;
        }
        case WifiState::WAITING_TO_RECONNECT: {
            if (now - _stateTimer >= _reconnectDelay) {
                transitionTo(WifiState::DISCONNECTED);
            }
            break;
        }
    }
}

bool WifiManager::isConnected() const {
    return _state == WifiState::CONNECTED;
}

WifiState WifiManager::getState() const {
    return _state;
}

} // namespace fastmin
