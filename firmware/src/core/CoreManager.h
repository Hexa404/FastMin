#pragma once

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

private:
    // Private constructors & operators to enforce singleton behavior
    CoreManager() = default;
    ~CoreManager() = default;
    CoreManager(const CoreManager&) = delete;
    CoreManager& operator=(const CoreManager&) = delete;
};

} // namespace fastmin
