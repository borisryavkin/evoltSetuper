#include <Keyboard.h>

const unsigned long INTERVAL = 300000; // 5 minutes (ms)
unsigned long lastPress = 0;

void setup() {
  delay(2000);      // let OS detect the keyboard
  Keyboard.begin();
}

void loop() {
  unsigned long now = millis();

  if (now - lastPress >= INTERVAL) {
    Keyboard.write('y');           // press y
    delay(50);                     // tiny human-like gap
    Keyboard.write(KEY_RETURN);    // press Enter
    lastPress = now;
  }
}