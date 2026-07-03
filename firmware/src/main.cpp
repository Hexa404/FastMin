#include <Arduino.h>
#include "core/CoreManager.h"

void setup() {
    // Initialize the CoreManager singleton
    fastmin::CoreManager::getInstance().init();
}

void loop() {
    // Update the CoreManager singleton in a non-blocking loop
    fastmin::CoreManager::getInstance().update();
}
