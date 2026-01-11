#include <Keyboard.h>

enum KeyType { KEYCHAR, KEYSPECIAL };

struct Step {
  unsigned long t_ms;   // when to run (ms since start)
  KeyType type;
  uint16_t key;         // ASCII for KEYCHAR, or KEY_* for KEYSPECIAL
  uint16_t repeat;      // how many times
  uint16_t gap_ms;      // gap between repeats
};

unsigned long startMs;
int idx = 0;

void sendKey(const Step& s) {
  for (uint16_t i = 0; i < s.repeat; i++) {
    if (s.type == KEYCHAR) {
      Keyboard.write((char)s.key);
    } else {
      Keyboard.write((uint8_t)s.key);
    }
    if (s.gap_ms) delay(s.gap_ms);
  }
}

Step steps[] = {
  // Single-run macro sequence with small offsets
  {    0, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },
  {  150, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  {  300, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // 3x (UP + ENTER)
  {  450, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  {  600, KEYSPECIAL, KEY_RETURN,      1, 0 },

  {  750, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  {  900, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 1050, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 1200, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // UP + ENTER
  { 1350, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 1500, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // ESC
  { 1650, KEYSPECIAL, KEY_ESC,         1, 0 },

  // #comment# 3 right arrow
  { 1800, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },
  { 1950, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },
  { 2100, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },

  // 5x (UP + ENTER)
  { 2250, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 2400, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 2550, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 2700, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 2850, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 3000, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 3150, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 3300, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 3450, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 3600, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // 2x (UP + ENTER)
  { 3750, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 3900, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 4050, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 4200, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // RIGHT + ENTER, ENTER
  { 4350, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },
  { 4500, KEYSPECIAL, KEY_RETURN,      1, 0 },
  { 4650, KEYSPECIAL, KEY_RETURN,      1, 0 },
};

const int N = sizeof(steps) / sizeof(steps[0]);

void setup() {
  delay(2000);
  Keyboard.begin();
  startMs = millis();
}

void loop() {
  if (idx >= N) return;

  unsigned long now = millis() - startMs;
  if (now >= steps[idx].t_ms) {
    sendKey(steps[idx]);
    idx++;
  }
}
