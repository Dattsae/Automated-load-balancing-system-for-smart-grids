#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define RELAY_PIN 7
#define SENSOR_A_PIN A0  
#define SENSOR_B_PIN A1  


LiquidCrystal_I2C lcd(0x27, 16, 2);  


const float VOLTAGE_DIVIDER_RATIO = 23.5 / 5.0;

// Voltage thresholds
const float VOLTAGE_THRESHOLD = 5.0;    // Minimum voltage to consider a source active
const float SOURCE_A_LOW_MIN = 9.5;    // Low voltage range minimum
const float SOURCE_A_LOW_MAX = 9.8;    // Low voltage range maximum
const float SOURCE_A_RECOVERY = 11.2;   // Recovery voltage threshold


String currentSource = "DC";  
bool normalOperation = true; 
bool sourceALowVoltage = false; 

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Automated Load  ");
  lcd.setCursor(0, 1);
  lcd.print("Balancing System");
  delay(1500);
  lcd.clear();
}

void loop() {
  
  float voltageA = readVoltage(SENSOR_A_PIN);
  float voltageB = readVoltage(SENSOR_B_PIN);
  
 
  bool sourceAHasVoltage = (voltageA > VOLTAGE_THRESHOLD);
  bool sourceBHasVoltage = (voltageB > VOLTAGE_THRESHOLD);
  
 
  checkSourceAVoltage(voltageA);
  

  intelligentSourceSelection(sourceAHasVoltage, sourceBHasVoltage, voltageA, voltageB);
  
 
  displayStatus(currentSource, voltageA, voltageB);
  
  delay(100);
}

void checkSourceAVoltage(float voltageA) {
  
  if (voltageA >= SOURCE_A_LOW_MIN && voltageA <= SOURCE_A_LOW_MAX) {
    sourceALowVoltage = true;
  }
  
  else if (voltageA >= SOURCE_A_RECOVERY) {
    sourceALowVoltage = false;
  }
 
}

void intelligentSourceSelection(bool sourceAHasVoltage, bool sourceBHasVoltage, float voltageA, float voltageB) {
  
  if (sourceAHasVoltage && sourceBHasVoltage) {
    
    if (sourceALowVoltage) {
      digitalWrite(RELAY_PIN, HIGH); 
      currentSource = "AC";
      normalOperation = true;
    } 
    
    else {
      digitalWrite(RELAY_PIN, LOW);  
      currentSource = "DC";
      normalOperation = true;
    }
  }
 
  else if (sourceAHasVoltage && !sourceBHasVoltage) {
    digitalWrite(RELAY_PIN, LOW);    
    currentSource = "DC";
    normalOperation = false;          
  }
  
  else if (!sourceAHasVoltage && sourceBHasVoltage) {
    digitalWrite(RELAY_PIN, HIGH);    
    currentSource = "AC";
    normalOperation = false;          
  }
  
  else {
    
    normalOperation = false;          
  }
}

float readVoltage(int pin) {
  int raw = analogRead(pin);
  float voltage = raw * (5.0 / 1023.0) * VOLTAGE_DIVIDER_RATIO;
  return voltage;
}

void displayStatus(String activeSource, float voltageA, float voltageB) {
  lcd.setCursor(0, 0);
  lcd.print("DC:");
  lcd.print(voltageA, 1);
  lcd.print("V AC:");
  lcd.print(voltageB, 1);
  lcd.print("V");
  
  lcd.setCursor(0, 1);
  lcd.print("Using Power: ");
  lcd.print(activeSource);
  
  
  lcd.setCursor(15, 1);
  if (!normalOperation) {
    lcd.print("!");  
  } else if (sourceALowVoltage) {
    lcd.print("L");  
  } else {
    lcd.print("P");  
  }
}