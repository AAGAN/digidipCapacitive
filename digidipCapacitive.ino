#include "Buttons_library.h"
#include <Adafruit_ILI9341\Adafruit_ILI9341.h>
#include <Adafruit_FT6206_Library\Adafruit_FT6206.h>
#include <SPI\SPI.h>
#include <Wire\Wire.h>
#include <Adafruit-GFX-Library\Adafruit_GFX.h>
#include <SD\SD.h>


#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_FT6206 ctp = Adafruit_FT6206();

uint8_t nx = 0;
uint8_t ny = 0;
uint16_t tripod = 605; //mm

volatile bool saveOK = false;
const uint8_t saveInterruptPin = 24;

uint8_t readButtonPin = 23;

const uint8_t SSSD = 4;
File logfile;

void setup()
{
    
    tft.begin();
    Serial.begin(9600);
    tft.setRotation(2);
	uint32_t pDistant = 0; //previous distant reading from the sensor
	pinMode(readButtonPin, INPUT);
	digitalWrite(readButtonPin, HIGH);
	bool testType = true;
	uint16_t testDura = 20;

	if (!SD.begin(SSSD)) {
		error("cannot start the SD card!");
	}
    char filename[] = "file_00.TXT"; // { 'f', 'i', 'l', 'e', '_', '0', '0', '.', 'T', 'X', 'T', '\0' };//makeFilename();
    for (uint8_t i = 0; i < 100; i++)
    {
        //filename[3] = i / 100 + '0';
        filename[5] = (i / 10) % 10 + '0';
        filename[6] = i % 10 + '0';
        if (!SD.exists(filename)) {
            // only open a new file if it doesn't exist

            logfile = SD.open(filename, FILE_WRITE);
            break;  // leave the loop!
        }
    }
	logfile = SD.open(filename, FILE_WRITE);
	//-------------------------------------------
	attachInterrupt(saveInterruptPin, okToSave , FALLING); //Interrupt for saving data
	//-------------------------------------------
    if (!ctp.begin(40)) {  // pass in 'sensitivity' coefficient
        Serial.println("Couldn't start FT6206 touchscreen controller");
        while (1);
    }


    Buttons_libraryClass Buttons[150] = {
        
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 270, 238, 40, ILI9341_MAGENTA, "Button7"),

        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),

        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),

        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),

        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),

        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 270, 238, 40, ILI9341_MAGENTA, "Button7"),

        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),

        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 270, 238, 40, ILI9341_MAGENTA, "Button7"),

        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 270, 238, 40, ILI9341_MAGENTA, "Button7"),

        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),

        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 0, 238, 40, ILI9341_BLACK, "Button1"),
        Buttons_libraryClass(tft, 1, 45, 238, 40, ILI9341_RED, "Button2"),
        Buttons_libraryClass(tft, 1, 90, 238, 40, ILI9341_BLUE, "Button3"),
        Buttons_libraryClass(tft, 1, 135, 238, 40, ILI9341_DARKGREEN, "Button4"),
        Buttons_libraryClass(tft, 1, 180, 238, 40, ILI9341_DARKCYAN, "Button5"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 225, 238, 40, ILI9341_OLIVE, "Button6"),
        Buttons_libraryClass(tft, 1, 270, 238, 40, ILI9341_MAGENTA, "Button7")
    };

    
    //----------------------------------------------------------------------------------
    delay(1000);
    tft.fillScreen(ILI9341_BLACK);
    bool found = false;
    int numButtons = 2;
    Buttons_libraryClass typeButtons[2]
    {
        Buttons_libraryClass(tft, 1, 1, 238, 50, ILI9341_BLACK, "Residential"),
        Buttons_libraryClass(tft, 1, 61, 238, 50, ILI9341_BLACK, "Commercial")
        /*Buttons_libraryClass(tft, 1, 121, 238, 50, ILI9341_BLACK, "10x10"),
        Buttons_libraryClass(tft, 1, 181, 238, 50, ILI9341_BLACK, "12x12")*/
    };
    
    for (uint8_t i = 0; i < numButtons; i++)
    {
        typeButtons[i].activate(); delay(200); typeButtons[i].deactivate(); delay(200);
    }

    while (!found)
    {  
        TS_Point p = ctp.getPoint();
        for (uint8_t i = 0; i < numButtons; i++)
        {
            if (typeButtons[i].isPressed(p.x, p.y))
            {
                typeButtons[i].activate();
                testType = i;
                found = true;
            }
            if (found) break;
        }
    }

    //----------------------------------------------------------------------------------
    delay(1000);
    tft.fillScreen(ILI9341_BLACK);
    found = false;
    numButtons = 4;
    Buttons_libraryClass duraButtons[4]
    {
        Buttons_libraryClass(tft, 1, 1, 238, 50, ILI9341_BLACK, "30 min"),
            Buttons_libraryClass(tft, 1, 61, 238, 50, ILI9341_BLACK, "20 min"),
            Buttons_libraryClass(tft, 1, 121, 238, 50, ILI9341_BLACK, "10 min"),
            Buttons_libraryClass(tft, 1, 181, 238, 50, ILI9341_BLACK, "5 min")
    };

    for (uint8_t i = 0; i < numButtons; i++)
    {
        duraButtons[i].activate(); delay(200); duraButtons[i].deactivate(); delay(200);
    }

    while (!found)
    {
        TS_Point p = ctp.getPoint();
        for (uint8_t i = 0; i < numButtons; i++)
        {
            if (duraButtons[i].isPressed(p.x, p.y))
            {
                duraButtons[i].activate();
                if (i == 0)testDura = 30;
                if (i == 1)testDura = 20;
                if (i == 2)testDura = 10;
                if (i == 3)testDura = 5;
                found = true;
            }
            if (found) break;
        }
    }
//----------------------------------------------------------------------------------
    delay(1000);
    tft.fillScreen(ILI9341_BLACK);
    found = false;
    numButtons = 4;
    Buttons_libraryClass gridButtons[4]
	{
		Buttons_libraryClass(tft, 1, 1, 238, 50, ILI9341_BLACK, "6x6"),
		Buttons_libraryClass(tft, 1, 61, 238, 50, ILI9341_BLACK, "8x8"),
		Buttons_libraryClass(tft, 1, 121, 238, 50, ILI9341_BLACK, "10x10"),
		Buttons_libraryClass(tft, 1, 181, 238, 50, ILI9341_BLACK, "12x12")
	};

    for (uint8_t i = 0; i < numButtons; i++)
	{
		gridButtons[i].activate(); delay(200); gridButtons[i].deactivate(); delay(200);
	}

	while (!found)
	{
		TS_Point p = ctp.getPoint();
        for (uint8_t i = 0; i < numButtons; i++)
		{
			if (gridButtons[i].isPressed(p.x, p.y))
			{
				gridButtons[i].activate();
				nx = 2 * i + 6;
				ny = nx;
                found = true;
			}
            if (found) break;
		}
	}

	//----------------------------------------------------------------------------------
    //Writing the header of the file 
    writeHeader(testType, testDura);
    //----------------------------------------------------------------------------------

	delay(1000);
    tft.fillScreen(ILI9341_BLACK);

    for (uint16_t j = 0; j < ny;j++)
    {
        for (uint16_t i = 0; i < nx; i++)
        {
            Buttons[j*ny + i].setX(i*ILI9341_TFTWIDTH/nx);
            Buttons[j*ny + i].setY(j*ILI9341_TFTWIDTH/ny);
            Buttons[j*ny + i].setWidth(ILI9341_TFTWIDTH/nx);
            Buttons[j*ny + i].setHeight(ILI9341_TFTWIDTH/ny);
            Buttons[j*ny + i].setFillColor(ILI9341_BLACK);
            Buttons[j*ny + i].setText(String(nx*ny - (j*nx + i)), 1);
            delay(50); Buttons[j*ny+i].activate(); delay(50); Buttons[j*ny+i].deactivate();
        }
        
    }
    uint16_t previousBucket = 0;
    while (1)
    {
        TS_Point p = ctp.getPoint();
		found = false;
        for (uint16_t j = 0; j < ny; j++)
        {
            for (uint16_t i = 0; i < nx; i++)
            {
                if (Buttons[j*ny + i].isPressed(p.x, p.y))
                {
                    Buttons[previousBucket].deactivate();
                    Buttons[j*ny + i].activate();
                    previousBucket = j*ny + i;
					found = true;
                }
				if (found) break;
            }
			if (found) break;
        }

		bool readButton = digitalRead(readButtonPin);

		while (!readButton)
		{
			uint32_t distant = getDistant();
			if (distant != pDistant)
			{
				pDistant = distant;
				tft.setCursor(1, 300);
				tft.print("Distant from the sensor is ");
				tft.print(distant);
				tft.println(" mm");
				tft.print("Depth of the water is ");
				tft.print(tripod - distant);
				tft.println(" mm");
			}
			readButton = digitalRead(readButtonPin);
			float depth = tripod - distant;
			float dnst = density(depth, testType, testDura);
			if (saveOK)
			{
				for (uint16_t i = 0; i < nx*ny; i++)
				{
					saveData(indexToBucket(i), dnst);
				}
				logfile.flush();
				
				saveData(previousBucket, dnst); // saves the data related to the active cell to the active cell's members
				Buttons[previousBucket].setFillColor(calcColor(depth,testType,testDura));
				Buttons[previousBucket].activate();
				Buttons[previousBucket].deactivate();
				Buttons[indexToBucket(previousBucket+1)].activate();
				saveOK = false;
				while (!digitalRead(readButton)){ 1; }
			}
		} 
    }
}

float density(uint16_t depth, bool testType, uint16_t testDura)//Calculates the density from depth and returns the density
{
	float L1 = 0.0, L12 = 0.0;// if testType is 0 then it is a residential test, if testType is 1 then it is a commercial test
	if (testType){ L1 = 444.5; L12 = 197580.25; } // mm, mm^2 , commercial
	else { L1 = 250.825; L12 = 62913.1806; } // mm, mm^2, residential
	float depthf = (float)depth; // mm
	float weight = depthf*(L12 + L1*depthf*0.12233 + depthf*depthf*0.4988E-2)*2.2e-6; 
	float density = weight * 0.119828 / (float)testDura;
}

uint16_t bucketToIndex(uint16_t bucket) //Calculates the index from bucket number
{
    uint16_t index = bucket;
	return index;
}

uint16_t calcColor(uint16_t depth, bool testType, uint8_t testDura)//Calculates the color based on the depth
{
	float D = density(depth, testType, testDura);
	if (D < 0.005)  return ILI9341_RED;
	if (D < 0.010) return ILI9341_ORANGE;
	if (D < 0.015) return ILI9341_GREENYELLOW;
	if (D < 0.020) return ILI9341_GREEN;
	return ILI9341_DARKGREEN; //anything more than 0.020 return darkgreen
}

uint16_t indexToBucket(uint16_t index)
{
	uint16_t bucketNo = index;
	return bucketNo;
}

void loop()
{
    
}

//String makeFilename()// creates a new filename
//{
//	String name = "File_00.TXT";
//    for (uint8_t i = 0; i < 100; i++) {
//        //filename[3] = i / 100 + '0';
//        name[5] = (i / 10) % 10 + '0';
//        name[6] = i % 10 + '0';
//        if (!SD.exists(name)) {
//            // only open a new file if it doesn't exist
//
//            logfile = SD.open(name, FILE_WRITE);
//            break;  // leave the loop!
//        }
//    } 
//	return name;
//}

void writeHeader(bool testType, uint16_t testDura)
{
	logfile.println("Project Number = \t Unknown");
	logfile.println("Project Name = \t Unknown");
	logfile.println("Test Number = \t Unknown");
	logfile.print("Test Description= \t");
	if (testType)
	{
		logfile.print(" Commercial");
	}
	else
	{
		logfile.print(" Residential (");
	}
	logfile.print(testDura);
	logfile.println(" min)");
	logfile.println("Date/Time= \t");

	logfile.println("Bucket# \t Density(gpm/(ft^2))");
	logfile.flush();
}

void saveData(uint16_t bucketNumber, float density)
{
	logfile.print(bucketNumber);
	logfile.print(" , ");
	logfile.println(density);
}

int getDistant()
{
	uint32_t distant = 0;
	int incomingByte = 0;
	
	while (incomingByte != 'R'){ incomingByte = Serial.read(); delay(10); }
	while (Serial.available() < 5){ delay(10); }

	// the format of the output from the sensor is :
	// R0000(ASCII 13)

	distant += 1000 * (Serial.read() - '0'); delay(10);
	distant += 100 * (Serial.read() - '0'); delay(10);
	distant += 10 * (Serial.read() - '0'); delay(10);
	distant += Serial.read() - '0'; delay(10);

	Serial.read();
	if (distant < 0)distant = 0;
	if (distant > 5000) distant = 5000;
	return distant;
}

void okToSave()
{
	saveOK = true;
}

void error(String text)
{
	Serial.println(text);
	while (1);
}