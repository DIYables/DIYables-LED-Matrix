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

#ifndef DIYables_MAX7219_H
#define DIYables_MAX7219_H

#include <SPI.h>
#include <DIYables_Matrix_Font.h>

class DIYables_Max7219 {
public:
    DIYables_Max7219(uint8_t csPin, uint8_t numMatrices = 4);
    void clear();
    void show();
    void setBrightness(uint8_t brightness);
    int16_t print(const char* text, uint8_t spacing = 2, int16_t col = 0);
    uint8_t printChar(char c, int16_t startCol = 0);
    uint8_t printBitmap(const uint8_t* bitmap, int16_t startCol = 0);
    uint8_t printCustomChar(const uint8_t* bitmap, int16_t col = 0);
    uint16_t getDisplayWidth() const;
    uint8_t getDisplayHeight() const;
    uint8_t getCharWidth(char c);
    uint16_t getTextWidth(const char* text, uint8_t spacing = 2);

private:
    void initialize();
    void sendCommandAll(uint8_t registerAddr, uint8_t data);
    void trimCharacter(const uint8_t* bitmap, uint8_t& left, uint8_t& right);

    uint8_t csPin;
    uint8_t numMatrices;
    uint16_t displayWidth;
    uint8_t displayHeight;
    uint32_t displayBuffer[8];
    DIYables_Font font;
};

#endif // DIYables_MAX7219_H
