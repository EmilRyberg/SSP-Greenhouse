void setup() {
    Serial.begin(115200);
    Serial.println("Init");
}

void loop() {
    if (Serial.available()) {
        delay(100);
        Serial.find("{");
        while (Serial.peek() != '}') {
            long pin = Serial.parseInt();
            long method = Serial.parseInt();
            long value = Serial.parseInt();
            Serial.print("pin: ");
            Serial.print(pin);
            Serial.print(" method: ");
            Serial.print((method == 1) ? "analog" : "digital");
            Serial.print(" ");
            Serial.println(value);
        }
        while (Serial.available()) {
            Serial.read();
        }
    }
    delay(1000);
}
