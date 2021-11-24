/*
 * A very simple test program exercising the Adafruit GFX library for an SSD1306 display.
 * 
 * Demos a few different fonts and drawing on the display a set of sine and cosine waves.
 * Shows the FPS that the drawing is achieving.
 * Shows drawing a simple button with the Adafruit_GFX_Button
 * 
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBoldOblique9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>

typedef struct {
  const char* fontName;
  const GFXfont* font;
} fontList_t;

fontList_t fonts[] = {
  {"FreeMono9pt7b", &FreeMono9pt7b},
  {"FreeMonoBold9pt7b", &FreeMonoBold9pt7b},
  {"FreeMonoBoldOblique9pt7b", &FreeMonoBoldOblique9pt7b},
  {"FreeMonoOblique9pt7b", &FreeMonoOblique9pt7b},
  {"FreeSans9pt7b", &FreeSans9pt7b},
  {"FreeSerif9pt7b", &FreeSerif9pt7b},
  {NULL, NULL}
};

Adafruit_SSD1306 display(128, 64);
const float twoPI = 2.0 * 3.14159;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(3000);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Failed to initialize the display!");
    while(1);
  }

  drawFontTest();
}

void drawFontTest() {

  for (int i = 0; fonts[i].fontName != NULL; i++) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display.setFont(fonts[i].font);
    display.setCursor(0, 20);
    display.write(fonts[i].fontName);
    display.display();
    delay(3000);
    display.clearDisplay();
    display.setCursor(0, 10);
    for (int i = 32; i < 128; i++) {
      display.write(i);
    }
    display.display();
    delay(5000);   
  }
  
}

void draw() {

  // draw a line across the display
  display.clearDisplay();
  for (int x = 0; x <= display.width(); x++) {
    // draw a straight line
    display.drawPixel(x, display.height() / 2, SSD1306_WHITE);
    // draw a sine wave
    display.drawPixel(x, display.height() / 2 - sin(twoPI * x / display.width()) * display.height() / 2 , SSD1306_WHITE);
    // draw an inverse sine wave
    display.drawPixel(x, display.height() / 2 + sin(twoPI * x / display.width()) * display.height() / 2, SSD1306_WHITE);
    // draw a cosine wave
    display.drawPixel(x, display.height() / 2 + cos(twoPI * x / display.width()) * display.height() / 2, SSD1306_WHITE);
    // draw an inverse cosine wave
    display.drawPixel(x, display.height() / 2 - cos(twoPI * x / display.width()) * display.height() / 2, SSD1306_WHITE);
  }
}

float fps = 0.0;

void loop() {
  // put your main code here, to run repeatedly:

  int startMillis = millis();
  draw();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setFont(NULL);  // use the default font
  display.setCursor(0,0);
  display.print("FPS = ");
  int duration = millis() - startMillis;
  fps = 0.9f * fps + 0.1f * (1000.0f / duration);
  display.print(fps);

  Adafruit_GFX_Button button1;
  button1.initButton(&display, 20, 20, 40, 20, 1, 0, SSD1306_WHITE, "Test", 1);
  button1.drawButton();
  display.display();
}
