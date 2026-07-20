// --- NAVAL AUTOMATED BILGE SYSTEM ---

const int pumpPin = 27;         // Triggers Motor Driver (IN1)
const int mainFloatPin = 32;    // Single Float Switch (Trigger & Kill)
const int acs712Pin = 35;       // Engine Telemetry Sensor
const int maintenancePin = 26;  // Philips Lamp Switch (Manual Override)

bool isPumping = false;       
bool manualOverrideTriggered = false; // Memory flag to separate Auto vs Manual stops

int pumpLoopCount = 0;        
int standbyLoopCount = 0;     // Controls the Heartbeat timing

void setup() {
  Serial.begin(115200);
  
  pinMode(pumpPin, OUTPUT);
  pinMode(mainFloatPin, INPUT_PULLUP);
  pinMode(maintenancePin, INPUT_PULLUP); 
  
  digitalWrite(pumpPin, LOW); 
  
  delay(1000); // Brief pause to let USB connect
  
  Serial.println("\n========================================");
  Serial.println("[INIT] BILGE SYSTEM ACTIVE");
  Serial.println("========================================");
}

void loop() {
  // 1. Read Sensors & Switches
  int waterState = digitalRead(mainFloatPin);
  bool isMaintenanceMode = (digitalRead(maintenancePin) == LOW); 
  
  // 2. Read Telemetry
  int rawCurrent = analogRead(acs712Pin);
  float sensorVoltage = (rawCurrent * 3.3) / 4095.0;

  // --- 3A. MANUAL OVERRIDE ---
  if (isMaintenanceMode) {
    if (isPumping == false) {
      Serial.println("\n[SYS] Manual override active. Completely clearing the tank.");
      digitalWrite(pumpPin, HIGH);
      isPumping = true;
      manualOverrideTriggered = true; // Tell the brain the human took over
    }
    
    if (pumpLoopCount % 5 == 0) { Serial.print("."); }
    pumpLoopCount++;
  } 
  
  // --- 3B. AUTOMATED MODE ---
  else {
    
    // SCENARIO A: Human just turned the switch OFF
    if (isPumping == true && manualOverrideTriggered == true) {
      Serial.println(" [DONE]");
      Serial.println("[SECURE] System returned to Auto. Pump halted.");
      digitalWrite(pumpPin, LOW);
      isPumping = false;
      manualOverrideTriggered = false; // Reset the human override memory
      standbyLoopCount = 0;
    }
    
    // SCENARIO B: AUTOMATED FLOOD DETECTED (Water lifts float)
    else if (waterState == HIGH && isPumping == false) {
      Serial.println("\n[CRITICAL] FLOOD DETECTED. PUMP ENGAGED.");
      Serial.print("[TELEMETRY] Engine Load: ");
      Serial.print(sensorVoltage);
      Serial.print("V | Evacuating ");
      
      digitalWrite(pumpPin, HIGH); 
      isPumping = true;
      manualOverrideTriggered = false; 
      pumpLoopCount = 0; 
    }
    
    // SCENARIO C: AUTOMATED SAFE SHUTOFF (Water drops float)
    else if (waterState == LOW && isPumping == true && manualOverrideTriggered == false) {
      Serial.println(" [DONE]"); 
      
      Serial.println("[SECURE] Evacuation complete. Reserve puddle left to prevent cavitation. [AUTO MODE]");
      
      digitalWrite(pumpPin, LOW); 
      isPumping = false;
      standbyLoopCount = 0; 
    }

    // 4. Clinical UI Dashboard 
    if (isPumping) {
      if (pumpLoopCount % 5 == 0) { Serial.print("."); }
      pumpLoopCount++;
    } else {
      // Standby Heartbeat updated to reflect Auto Mode status
      if (standbyLoopCount % 30 == 0) {
        Serial.println("[SYS] Hull integrity nominal. Sensors active. [AUTO MODE]");
      }
      standbyLoopCount++;
    }
  }

  // Fast 100ms scan rate for instant physical reaction
  delay(100); 
}
