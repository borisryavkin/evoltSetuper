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

// EXAMPLE ONLY (safe demo): ESC 10x over 2s, then Right, Up, Enter.
Step steps[] = {

  // ESC spam for 30 seconds (every 200 ms)
  { 0,      KEYSPECIAL, KEY_ESC, 150, 200 },   // 30s total

  // After 30 seconds (30000 ms)
  { 30000, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },
  { 30150, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 30300, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // 3x (UP + ENTER wlan off)
  { 30450, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },

  { 30750, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },

  { 31050, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 31200, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // UP + ENTER
  { 31350, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 31500, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // ESC
  { 31650, KEYSPECIAL, KEY_ESC,          1, 0 },

  // #comment# 3 right arrow
  { 31800, KEYSPECIAL, KEY_RIGHT_ARROW,  1, 0 },
  { 31950, KEYSPECIAL, KEY_RIGHT_ARROW,  1, 0 },
  { 32100, KEYSPECIAL, KEY_RIGHT_ARROW,  1, 0 },

  // 5x (UP + ENTER)
  { 32250, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },


  { 32550, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 32700, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 32850, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 33000, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 33150, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 33300, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 33450, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 33600, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // 2x (UP + ENTER)
  { 33750, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 33900, KEYSPECIAL, KEY_RETURN,      1, 0 },

  { 34050, KEYSPECIAL, KEY_UP_ARROW,    1, 0 },
  { 34200, KEYSPECIAL, KEY_RETURN,      1, 0 },

  // RIGHT + ENTER, ENTER
  { 34350, KEYSPECIAL, KEY_RIGHT_ARROW, 1, 0 },
  { 34500, 
  KEYSPECIAL, KEY_RETURN,      1, 0 },
{ 34650, KEYSPECIAL, KEY_RETURN,      1, 0 },
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
