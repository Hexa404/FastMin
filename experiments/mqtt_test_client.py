#!/usr/bin/env python3
import time
import sys

try:
    import paho.mqtt.client as mqtt
except ImportError:
    print("Error: 'paho-mqtt' library is not installed.")
    print("Please install it by running: pip install paho-mqtt")
    sys.exit(1)

# MQTT Configuration
MQTT_BROKER = "broker.hivemq.com"
MQTT_PORT = 1883
TOPIC_CONTROL = "fastmin/test/control"
TOPIC_STATUS = "fastmin/test/status"

# Callbacks
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print(f"Successfully connected to MQTT Broker: {MQTT_BROKER}")
        # Subscribe to status messages from the ESP32
        client.subscribe(TOPIC_STATUS)
        print(f"Subscribed to topic: {TOPIC_STATUS}")
    else:
        print(f"Failed to connect, return code {rc}")

def on_message(client, userdata, msg):
    print(f"\n[Incoming Message] Topic: {msg.topic}")
    print(f"Payload: {msg.payload.decode('utf-8')}")

def main():
    print("=========================================")
    print("FastMin MQTT Test Client")
    print("=========================================")

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    try:
        client.connect(MQTT_BROKER, MQTT_PORT, 60)
    except Exception as e:
        print(f"Could not connect to broker: {e}")
        sys.exit(1)

    # Start the network loop in the background
    client.loop_start()
    time.sleep(1)  # Wait for connection to establish

    # Publish a test control command to the ESP32
    test_payload = "HELLO FROM MAC COMPILER! MQTT IS WORKING!"
    print(f"\nPublishing test message to topic: {TOPIC_CONTROL}")
    print(f"Payload: '{test_payload}'")
    
    client.publish(TOPIC_CONTROL, test_payload)

    print("\nListening for messages... Press Ctrl+C to exit.")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nExiting test client.")
    finally:
        client.loop_stop()
        client.disconnect()

if __name__ == "__main__":
    main()
