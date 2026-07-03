#pragma once

#include <string>
#include <vector>
#include <functional>
#include <WiFi.h>
#include <PubSubClient.h>

namespace fastmin {

/**
 * @typedef MqttCallback
 * @brief Callback function type for MQTT message reception.
 */
using MqttCallback = std::function<void(const std::string& topic, const std::string& payload)>;

/**
 * @struct MqttSubscription
 * @brief Representation of an active MQTT subscription and its target callback.
 */
struct MqttSubscription {
    std::string topic;
    MqttCallback callback;
};

/**
 * @class MqttManager
 * @brief Manages MQTT connectivity, subscriptions, and publication.
 */
class MqttManager {
public:
    MqttManager();
    ~MqttManager() = default;

    /**
     * @brief Initialize MQTT client configuration.
     * @return true if initialization succeeded.
     */
    bool init();

    /**
     * @brief Run the MQTT state machine and client loop.
     * Non-blocking.
     */
    void update();

    /**
     * @brief Publish a message to a topic.
     * @param topic The MQTT topic string.
     * @param payload The message payload.
     * @param retained True to retain the message on broker.
     * @return true if successfully published.
     */
    bool publish(const std::string& topic, const std::string& payload, bool retained = false);

    /**
     * @brief Subscribe to an MQTT topic with a callback handler.
     * @param topic The MQTT topic string.
     * @param callback The handler callback.
     * @return true if subscription structure recorded successfully.
     */
    bool subscribe(const std::string& topic, MqttCallback callback);

    /**
     * @brief Check if currently connected to MQTT broker.
     * @return true if connected.
     */
    bool isConnected();

private:
    WiFiClient _wifiClient;
    PubSubClient _mqttClient;

    std::string _broker;
    uint16_t _port = 1883;
    std::string _user;
    std::string _pass;
    std::string _clientId;

    std::vector<MqttSubscription> _subscriptions;
    bool _connected = false;
    unsigned long _lastConnectAttempt = 0;
    unsigned long _reconnectInterval = 5000; // 5 seconds

    bool connect();
    void onMessage(char* topic, byte* payload, unsigned int length);
};

} // namespace fastmin
