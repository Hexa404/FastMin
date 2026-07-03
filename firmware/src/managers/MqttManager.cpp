#include "MqttManager.h"
#include "../core/CoreManager.h"
#include <Arduino.h>

namespace fastmin {

MqttManager::MqttManager() : _mqttClient(_wifiClient) {}

bool MqttManager::init() {
    auto& config = CoreManager::getInstance().getConfig();
    _broker = config.get<std::string>("mqtt_broker", "broker.hivemq.com");
    _port = static_cast<uint16_t>(config.get<int>("mqtt_port", 1883));
    _user = config.get<std::string>("mqtt_user", "");
    _pass = config.get<std::string>("mqtt_pass", "");
    
    // Generate standard client ID if none is configured
    std::string customClientId = config.get<std::string>("mqtt_client_id", "");
    if (!customClientId.empty()) {
        _clientId = customClientId;
    } else {
        uint8_t mac[6];
        WiFi.macAddress(mac);
        char idBuf[32];
        snprintf(idBuf, sizeof(idBuf), "FastMin_%02X%02X%02X%02X%02X%02X", 
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        _clientId = idBuf;
    }

    _mqttClient.setServer(_broker.c_str(), _port);
    
    // Register the message callback
    _mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->onMessage(topic, payload, length);
    });

    Serial.print("MqttManager initialized. Client ID: ");
    Serial.println(_clientId.c_str());
    return true;
}

bool MqttManager::connect() {
    Serial.print("MQTT: Connecting to ");
    Serial.print(_broker.c_str());
    Serial.print(":");
    Serial.println(_port);

    bool success = false;
    if (!_user.empty() && !_pass.empty()) {
        success = _mqttClient.connect(_clientId.c_str(), _user.c_str(), _pass.c_str());
    } else {
        success = _mqttClient.connect(_clientId.c_str());
    }

    if (success) {
        Serial.println("MQTT: Connected successfully.");
        // Resubscribe to all active topics
        for (const auto& sub : _subscriptions) {
            _mqttClient.subscribe(sub.topic.c_str());
            Serial.print("MQTT: Resubscribed to ");
            Serial.println(sub.topic.c_str());
        }
        return true;
    } else {
        Serial.print("MQTT: Connection failed, rc=");
        Serial.println(_mqttClient.state());
        return false;
    }
}

void MqttManager::update() {
    // We can only process MQTT when WiFi is connected
    if (!WiFi.isConnected()) {
        if (_connected) {
            Serial.println("MQTT: Disconnected due to WiFi connection loss.");
            _connected = false;
        }
        return;
    }

    if (!_mqttClient.connected()) {
        _connected = false;
        unsigned long now = millis();
        if (now - _lastConnectAttempt >= _reconnectInterval) {
            _lastConnectAttempt = now;
            _connected = connect();
        }
    } else {
        _mqttClient.loop();
    }
}

bool MqttManager::publish(const std::string& topic, const std::string& payload, bool retained) {
    if (!_mqttClient.connected()) {
        Serial.println("MQTT: Cannot publish, client not connected.");
        return false;
    }
    return _mqttClient.publish(topic.c_str(), payload.c_str(), retained);
}

bool MqttManager::subscribe(const std::string& topic, MqttCallback callback) {
    // Record subscription
    _subscriptions.push_back({topic, callback});

    // If already connected, subscribe immediately
    if (_mqttClient.connected()) {
        Serial.print("MQTT: Subscribing to ");
        Serial.println(topic.c_str());
        return _mqttClient.subscribe(topic.c_str());
    }
    return true;
}

bool MqttManager::isConnected() {
    return _mqttClient.connected();
}

void MqttManager::onMessage(char* topic, byte* payload, unsigned int length) {
    std::string topicStr(topic);
    std::string payloadStr((char*)payload, length);

    Serial.print("MQTT Received [");
    Serial.print(topicStr.c_str());
    Serial.print("]: ");
    Serial.println(payloadStr.c_str());

    // Dispatch to registered callbacks
    for (const auto& sub : _subscriptions) {
        if (sub.topic == topicStr) {
            if (sub.callback) {
                sub.callback(topicStr, payloadStr);
            }
        }
    }
}

} // namespace fastmin
