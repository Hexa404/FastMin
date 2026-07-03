#include "DisplayManager.h"
#include <Arduino.h>

namespace fastmin {

// Helper to pad string to exactly 16 characters
static std::string padString(const std::string& str, size_t length = 16) {
    if (str.length() >= length) {
        return str.substr(0, length);
    }
    return str + std::string(length - str.length(), ' ');
}

DisplayManager::DisplayManager() : _display(0x27, 16, 2) {}

bool DisplayManager::init() {
    _display.init();
    _display.backlight();
    _display.clear();
    
    _stateTimer = millis();
    _animationTimer = millis();
    
    Serial.println("DisplayManager: 16x2 LCD initialized successfully.");
    return true;
}

void DisplayManager::setState(DisplayState newState) {
    if (_state != newState) {
        _state = newState;
        _stateTimer = millis();
        _display.clear(); // Clear display once on state change to reset characters
    }
}

DisplayState DisplayManager::getState() const {
    return _state;
}

unsigned long DisplayManager::getStateTimer() const {
    return _stateTimer;
}

void DisplayManager::showMessage(const std::string& line1, const std::string& line2, const std::string& line3) {
    _message1 = line1;
    _message2 = line2;
    _message3 = line3;
    setState(DisplayState::STATUS_CONNECTED);
}

void DisplayManager::showTalkingMessage(const std::string& msg) {
    _message1 = msg;
    setState(DisplayState::FACE_TALKING);
}

void DisplayManager::update() {
    switch (_state) {
        case DisplayState::BOOT:
            renderBootScreen();
            break;
        case DisplayState::WIFI_CONNECTING:
            renderWifiConnectingScreen();
            break;
        case DisplayState::STATUS_CONNECTED:
            renderStatusConnectedScreen();
            break;
        case DisplayState::FACE_IDLE:
            renderFaceIdleScreen();
            break;
        case DisplayState::FACE_TALKING:
            renderFaceTalkingScreen();
            break;
    }
}

void DisplayManager::renderBootScreen() {
    _display.setCursor(0, 0);
    _display.print(padString("   FastMin AI   ").c_str());
    
    // Animate a loading progress indicator on row 1
    unsigned long elapsed = millis() - _stateTimer;
    int progress = (elapsed / 300) % 16;
    std::string loadingBar = "";
    for (int i = 0; i < 16; i++) {
        if (i <= progress) {
            loadingBar += ">";
        } else {
            loadingBar += " ";
        }
    }
    _display.setCursor(0, 1);
    _display.print(loadingBar.c_str());
}

void DisplayManager::renderWifiConnectingScreen() {
    // Animate loading dots "Connecting WiFi..."
    unsigned long elapsed = millis() - _stateTimer;
    int dots = (elapsed / 400) % 4;
    std::string connStr = "WiFi Connecting";
    for (int i = 0; i < dots; i++) {
        connStr += ".";
    }
    
    _display.setCursor(0, 0);
    _display.print(padString(connStr).c_str());
    
    // Show static subtitle/message on row 1
    _display.setCursor(0, 1);
    _display.print(padString("SSID: Connecting").c_str());
}

void DisplayManager::renderStatusConnectedScreen() {
    // Since 16x2 LCD only has 2 rows, we only print message1 and message2.
    _display.setCursor(0, 0);
    _display.print(padString(_message1).c_str());
    
    _display.setCursor(0, 1);
    _display.print(padString(_message2).c_str());
}

void DisplayManager::renderFaceIdleScreen() {
    unsigned long now = millis();
    
    // Blink timing: blink eyes every 4 seconds, for 200ms
    unsigned long cycle = now - _animationTimer;
    if (cycle > 4000) {
        _blinkState = true;
        if (cycle > 4200) {
            _blinkState = false;
            _animationTimer = now; // reset cycle
        }
    }

    _display.setCursor(0, 0);
    if (_blinkState) {
        // Draw closed eyes face
        _display.print(padString("  FastMin (-_-) ").c_str());
    } else {
        // Draw normal eyes face
        _display.print(padString("  FastMin (o_o) ").c_str());
    }

    _display.setCursor(0, 1);
    _display.print(padString(" SYSTEM ONLINE  ").c_str());
}

void DisplayManager::renderFaceTalkingScreen() {
    unsigned long now = millis();
    
    // Alternate mouth shape (o_o) -> (o-o) every 150ms to simulate talking
    int speakFrame = (now / 150) % 2;
    
    _display.setCursor(0, 0);
    if (speakFrame == 0) {
        _display.print(padString("  FastMin (o_o) ").c_str());
    } else {
        _display.print(padString("  FastMin (o-o) ").c_str());
    }
    
    _display.setCursor(0, 1);
    _display.print(padString(_message1).c_str());
}

} // namespace fastmin
