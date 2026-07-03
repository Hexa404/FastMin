#!/usr/bin/env python3
import sys
import time
import speech_recognition as sr
import google.generativeai as genai
import paho.mqtt.client as mqtt

import os
import subprocess

# Configuration
MQTT_BROKER = "broker.hivemq.com"
MQTT_PORT = 1883
MQTT_TOPIC = "fastmin/test/control"

# Load Gemini API Key
GEMINI_API_KEY = os.environ.get("GEMINI_API_KEY")
if not GEMINI_API_KEY:
    # Try loading from local .env file
    env_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".env")
    if os.path.exists(env_path):
        with open(env_path, "r") as f:
            for line in f:
                if line.strip().startswith("GEMINI_API_KEY="):
                    GEMINI_API_KEY = line.strip().split("=", 1)[1].replace("'", "").replace('"', '')
                    break

if not GEMINI_API_KEY:
    print("[Error] GEMINI_API_KEY not found in environment or .env file.")
    print("[Info] Please create a '.env' file in the project root with: GEMINI_API_KEY=your_key")
    sys.exit(1)

# Initialize Gemini AI
print("[System] Configuring Gemini AI...")
genai.configure(api_key=GEMINI_API_KEY)

# Define model with strict system instructions to keep output short for 16x2 LCD
system_instruction = (
    "Kamu adalah FastMin, AI Workshop Copilot pintar berbasis mikrokontroler ESP32. "
    "Kamu diciptakan oleh Hexa404 (akhmadzaqir) untuk membantu proyek elektronika dan coding. "
    "Kamu terhubung ke LCD 16x2, koneksi WiFi/MQTT, dan memiliki mata robot yang bisa berkedip dan berbicara. "
    "Jawab semua pertanyaan tentang dirimu, penciptamu, atau apa pun secara sangat singkat (maksimal 30 karakter) "
    "agar pas di layar LCD. Contoh: jika ditanya 'siapa kamu', jawab 'Aku FastMin, AI Asisten!'."
)
model = genai.GenerativeModel(
    model_name="gemini-2.5-flash",
    system_instruction=system_instruction
)

# Connect to MQTT Broker
print(f"[MQTT] Connecting to {MQTT_BROKER}...")
client = mqtt.Client()
try:
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()
    print("[MQTT] Connected successfully.")
except Exception as e:
    print(f"[Error] Failed to connect to MQTT: {e}")
    sys.exit(1)

# Initialize Speech Recognizer
recognizer = sr.Recognizer()

# Adjust for ambient noise once on startup
try:
    with sr.Microphone() as source:
        print("[Voice] Adjusting for ambient noise, please remain silent for a second...")
        recognizer.adjust_for_ambient_noise(source, duration=1)
        print("[Voice] Ready.")
except Exception as e:
    print(f"[Error] Failed to access default microphone: {e}")
    print("[Tip] Make sure Python has permission to access the Microphone on macOS.")
    sys.exit(1)

def listen_and_process():
    try:
        with sr.Microphone() as source:
            print("\n==================================================")
            print("👉 Tekan [Enter] untuk mulai berbicara, atau ketik 'exit' untuk keluar: ", end="")
            user_in = input().strip().lower()
            if user_in == 'exit':
                return False

            print("🎤 Mendengarkan... Bicara sekarang!")
            # Record for up to 6 seconds max
            audio = recognizer.listen(source, timeout=5, phrase_time_limit=6)
            print("🔄 Memproses suara...")

            # Convert voice to text (Speech-to-Text)
            # Default to Indonesian (id-ID)
            query = recognizer.recognize_google(audio, language="id-ID")
            print(f"👤 Kamu berkata: \"{query}\"")

            if not query.strip():
                return True

            # Query Gemini AI
            print("🧠 Menanyakan ke Gemini AI...")
            response = model.generate_content(query)
            reply = response.text.strip()
            print(f"🤖 Jawaban AI: \"{reply}\"")

            # Speak the reply out loud using macOS built-in TTS (non-blocking)
            try:
                # Use Indonesian female voice "Damayanti" and set natural reading rate (-r 140)
                subprocess.Popen(["say", "-v", "Damayanti", "-r", "140", reply])
            except Exception as e:
                print(f"⚠️ [TTS Error] Gagal memutar suara: {e}")

            # Publish to ESP32 MQTT topic
            print(f"[MQTT] Mengirim jawaban ke ESP32 di topik '{MQTT_TOPIC}'...")
            client.publish(MQTT_TOPIC, reply)
            print("[System] Terkirim!")

    except sr.WaitTimeoutError:
        print("⚠️ [Timeout] Tidak ada suara terdeteksi.")
    except sr.UnknownValueError:
        print("⚠️ [Error] Suara tidak terbaca dengan jelas.")
    except sr.RequestError as e:
        print(f"⚠️ [Error] Layanan Speech Recognition error: {e}")
    except Exception as e:
        print(f"⚠️ [Error] Terjadi kesalahan: {e}")
    
    return True

if __name__ == "__main__":
    try:
        running = True
        while running:
            running = listen_and_process()
            time.sleep(0.5)
    except KeyboardInterrupt:
        print("\n[System] Keluar dari program.")
    finally:
        client.loop_stop()
        client.disconnect()
        print("[System] Selesai.")
