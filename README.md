# FastMin

### **FastMin — AI Workshop Assistant**

---

## 📌 Overview
**FastMin** is a modular, adaptive, and cloud-first AI Workshop Assistant. It is designed to act as an intelligent, physical co-pilot in the workshop environment.

Unlike traditional chatbots, FastMin is a platform built to be extensible and adapt over time.

## 🚀 Project Vision
The system architecture splits responsibilities to balance cost, performance, and flexibility:
* **Edge Terminal (ESP32)**: Handles hardware interfaces including Wi-Fi, Bluetooth, Audio, Display, GPIO, MQTT, and OTA updates.
* **Brain in the Cloud (Gemini/OpenAI)**: Runs heavy cognitive and reasoning tasks, keeping the hardware terminal simple and cost-effective.

## 🎯 Project Goals
* **Modular Architecture**: Easy insertion and removal of hardware modules, manager layers, and cloud services.
* **Adaptive Capabilities**: Easily customizable to different tasks in the workshop.
* **Cloud First**: Heavy lifting done in the cloud; edge device runs lightweight code.
* **Future-proof**: Written in modern C++ (Arduino framework) to be easily portable to more powerful chips like the ESP32-S3.

---

## 📂 Folder Structure

```text
FastMin/
├── firmware/           # ESP32 Firmware source code (PlatformIO project)
│   ├── platformio.ini  # PlatformIO configuration
│   ├── src/            # Source files
│   │   ├── core/       # Core system and manager skeletons
│   │   ├── managers/   # Component managers (Wi-Fi, EventBus, etc. - milestone placeholder)
│   │   ├── models/     # Data models and structures
│   │   ├── drivers/    # Hardware driver wrappers
│   │   ├── services/   # Cloud interface and communication services
│   │   └── utils/      # Utility helpers
│   ├── include/        # Global header files
│   ├── lib/            # Local libraries
│   ├── data/           # Filesystem data assets (SPIFFS/LittleFS)
│   └── test/           # Unit tests
│
├── docs/               # Project documentation
│   ├── architecture/   # Architecture and system design notes
│   ├── roadmap/        # Product milestones
│   ├── api/            # Local/Cloud API contracts
│   └── hardware/       # Pin maps, wiring diagrams, and component specs
│
├── hardware/           # Hardware design source files (KiCad/Gerbers)
├── assets/             # Asset files
│   ├── images/         # Documentation illustrations
│   ├── expressions/    # Display UI animations and expressions
│   ├── sounds/         # Prompt chime and audio assets
│   └── logo/           # Project logo designs
│
├── experiments/        # Research scripts and sandboxed tests
├── scripts/            # Automation, flash, and tooling scripts
├── .gitignore          # Git exclusion files
├── LICENSE             # Project license
└── README.md           # This file
```

---

## 🗺️ Roadmap

- [x] **Milestone 1: Project Foundation**
  - [x] Directory structure setup
  - [x] Base PlatformIO environment configuration
  - [x] `CoreManager` structure and main loop skeleton
- [ ] **Milestone 2: Basic Networking & Communication**
  - [ ] WiFi Manager and MQTT client integration
- [ ] **Milestone 3: Interface & Display**
  - [ ] Hardware driver wraps, screen output, and visual assets integration
- [ ] **Milestone 4: Cloud & AI Integration**
  - [ ] Audio capture and cloud AI interaction

---

## 📄 License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
