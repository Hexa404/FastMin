#pragma once

#include <string>
#include <WiFi.h>

namespace fastmin {

/**
 * @enum WifiState
 * @brief Represents the connection state of the WiFi interface.
 */
enum class WifiState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    WAITING_TO_RECONNECT
};

/**
 * @class WifiManager
 * @brief Manages WiFi connections in a non-blocking state machine.
 */
class WifiManager {
public:
    WifiManager() = default;
    ~WifiManager() = default;

    /**
     * @brief Initialize WiFi settings and values.
     * @return true if initialization succeeded.
     */
    bool init();

    /**
     * @brief Run the WiFi state machine update loop.
     * Guaranteed not to block execution.
     */
    void update();

    /**
     * @brief Check if currently connected to WiFi.
     * @return true if WL_CONNECTED.
     */
    bool isConnected() const;

    /**
     * @brief Get the current connection state.
     * @return WifiState current state.
     */
    WifiState getState() const;

private:
    WifiState _state = WifiState::DISCONNECTED;
    unsigned long _stateTimer = 0;
    unsigned long _reconnectDelay = 5000;       // Cooldown time before retrying connection (ms)
    unsigned long _connectionTimeout = 15000;  // Max duration allowed to attempt connection (ms)
    std::string _ssid;
    std::string _password;

    void transitionTo(WifiState newState);
};

} // namespace fastmin
