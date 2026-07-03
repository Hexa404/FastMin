#pragma once

#include <LiquidCrystal_I2C.h>
#include <string>

namespace fastmin {

/**
 * @enum DisplayState
 * @brief Identifies different screen visual states.
 */
enum class DisplayState {
    BOOT,
    WIFI_CONNECTING,
    STATUS_CONNECTED,
    FACE_IDLE,
    FACE_TALKING
};

/**
 * @class DisplayManager
 * @brief Manages the 16x2 I2C LCD display and characters drawing.
 */
class DisplayManager {
public:
    DisplayManager();
    ~DisplayManager() = default;

    /**
     * @brief Initalize I2C and LCD driver.
     * @return true if communication with LCD is successful.
     */
    bool init();

    /**
     * @brief Redraw the display based on current state.
     * Non-blocking.
     */
    void update();

    /**
     * @brief Shift active display state.
     * @param newState Target display state.
     */
    void setState(DisplayState newState);

    /**
     * @brief Retrieve active display state.
     * @return DisplayState current state.
     */
    DisplayState getState() const;

    /**
     * @brief Set and show direct text line by line.
     */
    void showMessage(const std::string& line1, const std::string& line2 = "", const std::string& line3 = "");

    /**
     * @brief Trigger talking state and set the spoken text on the screen.
     */
    void showTalkingMessage(const std::string& msg);

    /**
     * @brief Get the state timer for checking durations.
     * @return unsigned long state timer in ms.
     */
    unsigned long getStateTimer() const;

private:
    LiquidCrystal_I2C _display;
    DisplayState _state = DisplayState::BOOT;
    unsigned long _stateTimer = 0;
    unsigned long _animationTimer = 0;
    bool _blinkState = false;
    
    std::string _message1;
    std::string _message2;
    std::string _message3;

    void renderBootScreen();
    void renderWifiConnectingScreen();
    void renderStatusConnectedScreen();
    void renderFaceIdleScreen();
    void renderFaceTalkingScreen();
};

} // namespace fastmin
