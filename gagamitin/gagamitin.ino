const int L1 = 7;
const int L2 = 6;
const int L3 = 5;
const int BUZZER = 2; // Added buzzer on pin 4

void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(BUZZER, OUTPUT); // Set buzzer pin as output
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //set 1
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  // Activate buzzer when all outputs are LOW
  digitalWrite(BUZZER, HIGH);
  delay(4000);
  digitalWrite(BUZZER, LOW); // Turn off buzzer before changing LED states
  
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(L3, HIGH);
  delay(4000);
  
  //set 2
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(L3, LOW);
  delay(4000);
  
  //set 3
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(L3, HIGH);
  delay(4000);
  
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  delay(4000);
  
  //set 4
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, HIGH);
  delay(4000);
}