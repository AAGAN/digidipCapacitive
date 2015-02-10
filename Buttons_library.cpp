#include "Buttons_library.h"

//Buttons_libraryClass::Buttons_libraryClass()
//{
//    x = 1;
//    y = 1;
//    width = 40;
//    height = 20;
//    fillColor = 0x0000;
//    Adafruit_ILI9341 tft;
//}

//Buttons_libraryClass::Buttons_libraryClass(uint16_t tftcs, uint16_t tftdc) 
//	: tft(tftcs, tftdc)
//{
//	x = 1; 
//	y = 1; 
//	width = 40; 
//	height = 20; 
//	fillColor = 0x0000;
//    text = "0";
//	//state = false;
//};

Buttons_libraryClass::Buttons_libraryClass(Adafruit_ILI9341 btft,
    uint16_t bx, uint16_t by, uint16_t bwidth, uint16_t bheight,
    uint16_t bcolor, String btext) : tft(btft)
{
    x = bx;
    y = by;
    width = bwidth;
    height = bheight;
    fillColor = bcolor;
    borderColor = 0x7BEF;
    text = btext;
    textColor = ILI9341_DARKGREY;
    textSize = 1;
}

void Buttons_libraryClass::setX(uint16_t bx)
{
    x = bx;
}

void Buttons_libraryClass::setY(uint16_t by)
{
    y = by;
}

void Buttons_libraryClass::setWidth(uint16_t bwidth)
{
    width = bwidth;
}

void Buttons_libraryClass::setHeight(uint16_t bheight)
{
    height = bheight;
}

bool Buttons_libraryClass::isPressed(uint16_t touchX, uint16_t touchY)
{
    if (touchX > x && touchX < x + width)
    {
        if (touchY > y && touchY < y + height)
        {
            return true;
        }
    }
    return false;
}

//void setTft(Adafruit_ILI9341 btft) : tft(btft)
//{
//   
//}

//Buttons_libraryClass::Buttons_libraryClass(uint16_t tftcs, uint16_t tftdc, 
//	uint16_t bx, uint16_t by, uint16_t bwidth, uint16_t bheight, 
//	uint16_t bcolor, String btext) : tft(tftcs, tftdc)
//{
//	x = bx; 
//	y = by; 
//	width = bwidth; 
//	height = bheight; 
//	fillColor = bcolor;
//	borderColor = 0x7BEF;
//	text = btext;
//}

void Buttons_libraryClass::drawBorder(uint16_t color)
{
	tft.drawRect(x, y, width, height, borderColor);
}

void Buttons_libraryClass::fill(uint16_t color)
{
	tft.fillRect(x + 1, y + 1, width - 2, height - 2, fillColor);
}

void Buttons_libraryClass::activate()
{
	borderColor = ILI9341_YELLOW;
    textColor = ILI9341_YELLOW;
	show();
}

void Buttons_libraryClass::deactivate()
{
	borderColor = ILI9341_DARKGREY;
    textColor = ILI9341_DARKGREY;
	show();
}

void Buttons_libraryClass::show()
{
	drawBorder(borderColor);
	fill(fillColor);
	showText();
}

void Buttons_libraryClass::setFillColor(uint16_t color)
{
    fillColor = color;
}

void Buttons_libraryClass::showText()
{
    tft.setCursor(x+1, y+1);
    tft.setTextColor(textColor);  
    tft.setTextSize(textSize);
    tft.print(text);
}

String Buttons_libraryClass::getText()
{
	return text;
}

void Buttons_libraryClass::setText(String btext, uint8_t btextSize)
{
	text = btext;
    textSize = btextSize;
}

Buttons_libraryClass::~Buttons_libraryClass(){};

// Buttons_libraryClass Buttons_library;

