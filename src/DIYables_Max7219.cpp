/*
   Copyright (c) 2024, DIYables.io. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

   - Neither the name of the DIYables.io nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY DIYABLES.IO "AS IS" AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL DIYABLES.IO BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#include <DIYables_Max7219.h>

DIYables_Max7219::DIYables_Max7219(uint8_t csPin, uint8_t numMatrices)
  : csPin(csPin), numMatrices(numMatrices), displayHeight(8) {
  displayWidth = numMatrices * 8;
  memset(displayBuffer, 0, sizeof(displayBuffer));
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  initialize();
}

void DIYables_Max7219::initialize() {
  SPI.begin();
  sendCommandAll(0x0C, 0x01);  // Exit shutdown mode
  sendCommandAll(0x09, 0x00);  // Disable decode mode
  sendCommandAll(0x0A, 0x0F);  // Set intensity (0x00 to 0x0F)
  sendCommandAll(0x0B, 0x07);  // Set scan limit (0 to 7)
  sendCommandAll(0x0F, 0x00);  // Disable display test mode
}

void DIYables_Max7219::sendCommandAll(uint8_t registerAddr, uint8_t data) {
  digitalWrite(csPin, LOW);
  for (uint8_t i = 0; i < numMatrices; i++) {
    SPI.transfer(registerAddr);
    SPI.transfer(data);
  }
  digitalWrite(csPin, HIGH);
}

void DIYables_Max7219::clear() {
  memset(displayBuffer, 0, sizeof(displayBuffer));
}

void DIYables_Max7219::show() {
  for (uint8_t row = 0; row < displayHeight; row++) {
    digitalWrite(csPin, LOW);
    for (uint8_t matrix = 0; matrix < numMatrices; matrix++) {
      uint8_t dataByte = (displayBuffer[row] >> (8 * (numMatrices - 1 - matrix))) & 0xFF;
      SPI.transfer(row + 1);
      SPI.transfer(dataByte);
    }
    digitalWrite(csPin, HIGH);
  }
}

void DIYables_Max7219::trimCharacter(const uint8_t* bitmap, uint8_t& left, uint8_t& right) {
  left = 7;
  right = 0;
  for (uint8_t col = 0; col < 8; col++) {
    bool columnHasPixel = false;
    uint8_t mask = 1 << (7 - col);
    for (uint8_t row = 0; row < 8; row++) {
      uint8_t rowData = bitmap[row];

      if (rowData & mask) {
        columnHasPixel = true;
        break;
      }
    }
    if (columnHasPixel) {
      if (col < left) left = col;
      if (col > right) right = col;
    }
  }

  if (right < left) {
    left = 0;
    right = 0;
  }
}

void DIYables_Max7219::setBrightness(uint8_t brightness) {
  if (brightness <= 15) {
    sendCommandAll(0x0A, brightness);
  }
}

uint8_t DIYables_Max7219::printBitmap(const uint8_t* bitmap, int16_t startCol) {
  uint8_t left, right;
  trimCharacter(bitmap, left, right);
  uint8_t charWidth = right - left + 1;

  for (uint8_t row = 0; row < 8; row++) {
    uint8_t rowData = bitmap[row];

    for (uint8_t col = left; col <= right; col++) {
      int16_t colPos = startCol + (col - left);
      if (colPos >= 0 && colPos < displayWidth) {
        uint8_t bit = (rowData >> (7 - col)) & 0x01;
        if (bit) {
          displayBuffer[row] |= (1UL << (displayWidth - 1 - colPos));
        }
      }
    }
  }

  return charWidth;
}

uint8_t DIYables_Max7219::printChar(char c, int16_t startCol) {
  const uint8_t* bitmap = font.getChar(c);
  return printBitmap(bitmap, startCol);
}

int16_t DIYables_Max7219::print(const char* text, uint8_t spacing, int16_t col) {
  int16_t cursor = col;
  uint8_t ch = (uint8_t)*text;
  while (ch) {
    ch = (uint8_t)*text;
    text++;
    if (ch == 0xC2 && (uint8_t)*text == 0xB0) {
      continue;
    } else {
      uint8_t charWidth = printChar(ch, cursor);
      cursor += charWidth + spacing;
    }
  }

  return cursor;
}

uint8_t DIYables_Max7219::printCustomChar(const uint8_t* bitmap, int16_t col) {
  return printBitmap(bitmap, col);  // Set fromProgmem to false
}

uint16_t DIYables_Max7219::getDisplayWidth() const {
  return displayWidth;
}

uint8_t DIYables_Max7219::getDisplayHeight() const {
  return displayHeight;
}

uint8_t DIYables_Max7219::getCharWidth(char c) {
  const uint8_t* bitmap = font.getChar(c);
  uint8_t left, right;
  trimCharacter(bitmap, left, right);
  return right - left + 1;
}

uint16_t DIYables_Max7219::getTextWidth(const char* text, uint8_t spacing) {
  uint16_t totalWidth = 0;
  while (*text) {
    uint8_t charWidth = getCharWidth(*text);
    totalWidth += charWidth + spacing;
    text++;
  }
  if (totalWidth >= spacing)
    totalWidth -= spacing;  // Remove spacing after last character
  return totalWidth;
}
