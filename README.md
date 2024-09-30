## LED Matrix Library for Arduino, ESP32, ESP8266 - DIYables_LED_Matrix
This LED Matrix library is designed for Arduino, ESP32, ESP8266... to work with the Max7219 LED Matrix. It is created by DIYables to work with DIYables LED Matrix, but also work with other brand's LED Matrix. Please consider purchasing [LED Matrix 8x8](https://www.amazon.com/dp/B0D2K9ZLW6) and [LED Matrix 32x8](https://www.amazon.com/dp/B0BXKKT72V) from DIYables to support our work.


![LED Matrix](https://diyables.io/images/products/led-matrix.jpg)



Product Link
----------------------------
* [LED Matrix 8x8](https://diyables.io/products/dot-matrix-display-fc16-8x8-led)
* [LED Matrix 32x8](https://diyables.io/products/dot-matrix-display-fc16-4-in-1-32x4-led)



Features  
----------------------------  
* Supports ASCII characters, including the degree (°) symbol  
* Allows custom characters (with a provided custom character generator)  
* Trims each character to its actual width and adds configurable spacing, unlike other libraries that fix characters to 8-pixel width, for a more compact and flexible display  
* Compatible with any Arduino-API-supported platform, including Arduino, ESP32, ESP8266, and more


Available Functions
----------------------------
* `void clear()`
* `void show()`
* `void setBrightness(uint8_t brightness)`
* `int16_t print(const char* `text, uint8_t spacing = 2, int16_t col = 0)`
* `uint8_t printChar(char c, int16_t startCol = 0)`
* `uint8_t printBitmap(const uint8_t* `bitmap, int16_t startCol = 0)`
* `uint8_t printCustomChar(const uint8_t* `bitmap, int16_t col = 0)`
* `uint16_t getDisplayWidth()` const
* `uint8_t getDisplayHeight()` const
* `uint8_t getCharWidth(char c)`
* `uint16_t getTextWidth(const char* `text, uint8_t spacing = 2)`


Available Examples
----------------------------
`LED_Matrix.ino` does:
* display text
* display custom characters
* scroll text.py



Tutorials
----------------------------
* [Arduino - LED Matrix](https://arduinogetstarted.com/tutorials/arduino-led-matrix)
* [Arduino UNO R4 - LED Matrix](https://newbiely.com/tutorials/arduino-uno-r4/arduino-uno-r4-led-matrix)
* [Arduino Nano - LED Matrix](https://newbiely.com/tutorials/arduino-nano/arduino-nano-led-matrix)
* [Arduino Nano ESP32 - LED Matrix](https://newbiely.com/tutorials/arduino-nano-esp32/arduino-nano-esp32-led-matrix)
* [ESP32 - LED Matrix](https://esp32io.com/tutorials/esp32-led-matrix)
* [ESP8266 - LED Matrix](https://newbiely.com/tutorials/esp8266/esp8266-led-matrix)



References
----------------------------
* [DIYables_LED_Matrix Library Reference](https://arduinogetstarted.com/reference/library/diyables-led-matrix-library)



