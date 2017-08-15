PROJECT_DIR       = .
ARDMK_DIR         = $(PROJECT_DIR)/Arduino-Makefile
USER_LIB_PATH     = $(PROJECT_DIR)
ARDUINO_LIBS      = core/Singleton core/List core/Timer core/TimerZero core/Pins core/State core/Config core/ADCHandler \
                    lib/OneWire lib/Arduino-Temperature-Control-Library core/TemperatureSensor \
                    lib/SoftwareSerial lib/Stream lib/Fingerprint_Scanner-TTL/FPS_GT511C3 core/FingerprintScanner \
                    lib/PulseSensorBPM core/PulseSensor \
                    core/SerialCommunication \
                    lib/Adafruit_NeoPixel core/LedStrip \
                    core/GSRSensor

OTHER_LIBS        = -Wl,--allow-multiple-definition

include $(ARDMK_DIR)/Arduino.mk
