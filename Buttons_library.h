// Buttons_library.h
#include <Adafruit_ILI9341\Adafruit_ILI9341.h>
#include <SPI\SPI.h>
#include <Wire\Wire.h>
#include <Adafruit-GFX-Library\Adafruit_GFX.h>

#ifndef _BUTTONS_LIBRARY_h
#define _BUTTONS_LIBRARY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Buttons_libraryClass
{
 protected:
	 uint16_t x, y, width, height, fillColor, borderColor, textColor;
	 //bool state; 
	 /*uint16_t cs, dc;*/
	 Adafruit_ILI9341 tft;
	 String text;
     uint8_t textSize;
     void fill(uint16_t);
     void drawBorder(uint16_t);
     void showText();

 public:
    //Buttons_libraryClass();
    //Buttons_libraryClass(uint16_t, uint16_t);
     Buttons_libraryClass(Adafruit_ILI9341, uint16_t, uint16_t, uint16_t,
         uint16_t, uint16_t, String);
	//Buttons_libraryClass(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, 
	//	uint16_t, uint16_t, String);// , bool);
	~Buttons_libraryClass();
	void activate();
	void deactivate();
	void setText(String, uint8_t);
    void setFillColor(uint16_t);
	String getText();
	void show();
    void setX(uint16_t);
    void setY(uint16_t);
    void setWidth(uint16_t);
    void setHeight(uint16_t);
    bool isPressed(uint16_t, uint16_t);
    //void setTft(Adafruit_ILI9341);
};

//extern Buttons_libraryClass Buttons_library;

#endif

