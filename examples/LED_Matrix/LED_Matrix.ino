/*
   Created by DIYables

   This example code is in the public domain

   Product page:
   - https://diyables.io/products/dot-matrix-display-fc16-8x8-led
   - https://diyables.io/products/dot-matrix-display-fc16-4-in-1-32x4-led
*/

#include <DIYables_LED_Matrix.h>

#define CS_PIN 10       // Chip Select pin for MAX7219
#define NUM_MATRICES 4  // Number of cascaded MAX7219 modules
#define SPACING 2       // spacing between two characters

DIYables_Max7219 display(CS_PIN, NUM_MATRICES);

void setup() {
  Serial.begin(9600);
  delay(500);

  // Initialize the display
  display.setBrightness(1);  // Adjust brightness from 0 to 15

  // Clear the display
  display.clear();
  display.show();

  // Render text on the display
  display.print("27°C", SPACING, 2);  // Text, spacing, starting column
  display.show();
  delay(5000);

  // Clear the display
  display.clear();
  display.show();

  // Define custom characters
  uint8_t custom_char_1[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b11110000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
  };

  uint8_t custom_char_2[8] = {
    0b00000000,
    0b01101100,
    0b10010010,
    0b10000010,
    0b10000010,
    0b01000100,
    0b00101000,
    0b00010000
  };

  uint8_t custom_char_3[8] = {
    0b00000000,
    0b00100000,
    0b00010000,
    0b11111000,
    0b00010000,
    0b00100000,
    0b00000000,
    0b00000000
  };

  // Clear the display
  display.clear();
  display.printCustomChar(custom_char_1, 0);
  display.printCustomChar(custom_char_2, 4);
  display.printCustomChar(custom_char_3, 11);
  display.show();
  delay(5000);
}

void loop() {
  scrollText("Hello, DIYables");
}

void scrollText(const char* message) {
  uint16_t totalWidth = display.getTextWidth(message, SPACING);
  int16_t startPosition = display.getDisplayWidth();
  int16_t endPosition = -totalWidth;

  for (int16_t col = startPosition; col > endPosition; col--) {
    display.clear();
    display.print(message, SPACING, col);
    display.show();
    delay(50);  // Adjust speed here
  }
}
