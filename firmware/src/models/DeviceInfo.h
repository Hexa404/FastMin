#pragma once

#include <cstring>
#include <unordered_map>
#include <variant>
#include <optional>
#include <vector>
#include <bitset>

namespace fastmin {

/**
 * @enum DeviceType
 * @brief Strong-typed enumeration representing supported hardware peripherals.
 */
enum class DeviceType {
    UNKNOWN,
    DS18B20,
    DHT22,
    RELAY,
    LED,
    BUTTON,
    SERVO,
    PUMP,
    ULTRASONIC,
    TURBIDITY,
    FLOW_SENSOR
};

/**
 * @brief Convert DeviceType enum value to string.
 * @param type The DeviceType value.
 * @return std::string The string representation of the device type.
 */
std::string deviceTypeToString(DeviceType type);

/**
 * @brief Convert string representation to DeviceType enum value.
 * @param typeStr The string to convert.
 * @return DeviceType The matching enum value, or DeviceType::UNKNOWN.
 */
DeviceType stringToDeviceType(const std::string& typeStr);
// ---------------------------------------------------------------------------
// ConnectionInfo – future‑proof connection/interface description
// ---------------------------------------------------------------------------
struct ConnectionInfo {
    // NOTE: This struct represents a generic connection description.
    // It is aliased as ConnectionInfo for semantic clarity.
    // (see alias below)
    // NOTE: This struct represents a generic connection description.
    // It is aliased as ConnectionInfo for semantic clarity.

    // Single GPIO pin (e.g., simple relay or button)
    std::optional<uint8_t> gpio;
    // Multiple GPIO pins (e.g., parallel data bus)
    std::vector<uint8_t> gpio_multi;

    // I2C configuration – optional fields
    struct I2C {
        uint8_t bus = 0;      // I2C bus number (ESP32 has 0 and 1)
        uint8_t address = 0;  // 7‑bit slave address
    } i2c;

    // SPI configuration – optional fields
    struct SPI {
        uint8_t bus = 0;   // SPI host number
        uint8_t cs = 0;    // Chip‑Select pin
        uint8_t mosi = 0;  // Master‑Out‑Slave‑In pin
        uint8_t miso = 0;  // Master‑In‑Slave‑Out pin
        uint8_t sck = 0;   // Clock pin
    } spi;

    // UART configuration – optional fields
    struct UART {
        uint8_t uart_num = 0; // UART port number (0,1,2)
        uint8_t rx_pin = 0;   // Receive pin
        uint8_t tx_pin = 0;   // Transmit pin
    } uart;

    // Enumerates which interface is currently active for this device
    enum class Interface { None, GPIO, GPIO_MULTI, I2C, SPI, UART } active = Interface::None;
};

// ---------------------------------------------------------------------------
// Capability – bit‑mask describing what the device can do
// ---------------------------------------------------------------------------
enum class Capability : uint16_t {
    Temperature = 1 << 0,
    Humidity    = 1 << 1,
    Switch      = 1 << 2,
    PWM         = 1 << 3,
    Distance    = 1 << 4,
    Flow        = 1 << 5,
    Turbidity   = 1 << 6,
    // Add future capabilities here
};

using CapabilitySet = std::bitset<16>; // up to 16 capabilities now

using PropertyValue = std::variant<bool, int, float, double, std::string>;
using PropertyMap = std::unordered_map<std::string, PropertyValue>;
/**
 * @struct DeviceInfo
 * @brief Represents the metadata of a registered hardware device.
 * 
 * Houses standard fields required to identify and configure devices,
 * plus a dynamic property map to store device-specific attributes
 * (such as addresses, polling rates, thresholds) without breaking backward compatibility.
 */
struct DeviceInfo {


    std::string id;                                     ///< Unique device identifier (e.g. "temp_1", "relay_pump")
    std::string name;                                   ///< User-friendly device name (e.g. "Main Water Temp")
    DeviceType type = DeviceType::UNKNOWN;              ///< Type of the hardware device
    ConnectionInfo connection;                          ///< Connection description (future‑proof)
    CapabilitySet capabilities;                         ///< What the device can do
    bool enabled = true;                                ///< Active status flag
    std::string description;                            ///< Short description of the device's role/location

    // Dynamic property map for future‑proof parameters
    // without breaking backward compatibility.
    PropertyMap properties;
};

} // namespace fastmin
// Semantic alias for connection description

