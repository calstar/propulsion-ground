#define IGNITION_PIN (7)

void setup() {
    Serial.begin(9600);
    pinMode(IGNITION_PIN, OUTPUT);
    digitalWrite(IGNITION_PIN, 0);
}
void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        Serial.readString();
        if (input == "ignite") {
            Serial.print("Igniting in 3... "); Serial.flush();
            delay(1000);
            Serial.print("2... "); Serial.flush();
            delay(1000);
            Serial.print("1... "); Serial.flush();
            delay(1000);
            Serial.print("igniting!."); Serial.flush();
            digitalWrite(IGNITION_PIN, 1);
            delay(100);
            Serial.print("."); Serial.flush();
            delay(100);
            digitalWrite(IGNITION_PIN, 0);
            Serial.print(". done.\r\n"); Serial.flush();
        } else if (input == "off") {
            digitalWrite(IGNITION_PIN, 0);
            Serial.print("Turned off.\r\n");
        }
        Serial.readString();
    }
}
