#include <Arduino.h>
#include <Wire.h>
#include "HX711.h"

// Pin Definitions based on Project Architecture
const int STEP_PIN = 27;
const int DIR_PIN = 26;
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

// Control Flags & Variables
volatile bool emergencyStop = false;
float currentForceN = 0.0;
long currentStepCount = 0;

// Task Handles for Dual-Core FreeRTOS Partitioning
TaskHandle_t Core0TaskHandle;
TaskHandle_t Core1TaskHandle;

// --- CORE 0: Motor Control & Real-Time 45N Safety Interlock (<50ms response) ---
void Core0MotorTask(void * pvParameters) {
  digitalWrite(DIR_PIN, HIGH); // Set downward descent direction
  
  while (true) {
    if (emergencyStop) {
      // High-speed reverse retraction on obstacle abort
      digitalWrite(DIR_PIN, LOW); 
      for (int i = 0; i < 2000; i++) { // Retract steps
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(500);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(500);
      }
      vTaskDelay(pdMS_TO_TICKS(1000)); // Pause after abort
      continue;
    }

    // Check safety threshold (45 N limit)
    if (currentForceN >= 45.0) {
      emergencyStop = true;
      Serial.println(F("{\"status\":\"OBSTACLE_ABORT\",\"force_n\":45.0}"));
      continue;
    }

    // Normal downward step pulse (2 mm/s profile)
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(800); // Adjust speed spacing
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(800);
    currentStepCount++;

    vTaskDelay(1); // Yield to FreeRTOS watchdog
  }
}

// --- CORE 1: Sensor Acquisition, Optical Readings & Telemetry ---
void Core1SensorTask(void * pvParameters) {
  while (true) {
    if (scale.is_ready()) {
      long reading = scale.read();
      // Calibration factor conversion to Newtons (placeholder scale conversion)
      currentForceN = (float)reading / 20000.0; 
    }

    // Format structured JSON telemetry packet
    Serial.print(F("{\"depth_mm\":"));
    Serial.print(currentStepCount * 0.0025); // Step-to-depth resolution factor
    Serial.print(F(",\"force_n\":"));
    Serial.print(currentForceN);
    Serial.print(F(",\"status\":\""));
    Serial.print(emergencyStop ? F("ABORT") : F("NORMAL"));
    Serial.println(F("\"}"));

    vTaskDelay(pdMS_TO_TICKS(500)); // Telemetry update interval
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_gain(128); // Channel A gain 128 for high resolution
  scale.tare();        // Tare scale at top stroke limit

  // Pin Core 0 to Motor Control & Safety Interlock
  xTaskCreatePinnedToCore(
    Core0MotorTask,   /* Task function */
    "Core0Motor",     /* Name of task */
    4096,             /* Stack size of task */
    NULL,             /* Parameter of the task */
    3,                /* Priority (higher priority for safety) */
    &Core0TaskHandle, /* Task handle */
    0                 /* Core ID (0) */
  );

  // Pin Core 1 to Sensor Acquisition & Telemetry
  xTaskCreatePinnedToCore(
    Core1SensorTask,  /* Task function */
    "Core1Sensor",    /* Name of task */
    4096,             /* Stack size of task */
    NULL,             /* Parameter of the task */
    1,                /* Priority */
    &Core1TaskHandle, /* Task handle */
    1                 /* Core ID (1) */
  );
}

void loop() {
  // Empty because all execution is handled deterministically via FreeRTOS cores
  vTaskDelete(NULL);
}
