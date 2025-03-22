#include <Arduino_GFX_Library.h> 
/* V1.3.1 or V1.4.0 (see constructors below, higher than V1.4.0 does not work (29-01-2024) at the time of writing, also see: https://github.com/moononournation/Arduino_GFX/issues/417) 
 * (https://github.com/moononournation/Arduino_GFX) Can be installed via the library manager of the Arduino IDE
*/
#include <TAMC_GT911.h>
/* V1.0.2
 * (https://github.com/TAMCTec/gt911-arduino) Can be installed via the library manager of the Arduino IDE
*/

/* 
 *  If used with Arduino_GFX_Library.h V1.3.1 use the following constructors:
*/
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
  14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
  9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
  15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */
);

Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
  bus,
  800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
  480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */,
  1 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

/* 
 *  If used with Arduino_GFX_Library.h V1.4.0 use the following constructors:
*/
//Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
//    41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
//    14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
//    9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
//    15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */,
//    0 /* hsync_polarity */, 180 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
//    0 /* vsync_polarity */, 12 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */);
//
//Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
//    800 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */);


#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
#define TFT_BL 2


#define TOUCH_GT911
#define TOUCH_GT911_SCL 20
#define TOUCH_GT911_SDA 19
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST 38
#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 800
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 480
#define TOUCH_MAP_Y2 0

TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));


void setup(void)
{
  Serial.begin(115200);
  gfx->begin();
  gfx->fillScreen(BLACK);

#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif

  gfx->setCursor(10, 10);
  gfx->setTextColor(RED);
  gfx->println("Hello World!");

  delay(1000); // 1 seconds

  ts.begin();
  ts.setRotation(1);


  gfx->fillScreen(BLACK);
  gfx->setCursor(0, 0);
  gfx->print("ESP32-8048S070C touch test:");
  gfx->setTextColor(GREEN);
  Serial.println(digitalRead(-1));
}

void loop() {
  ts.read();
  if (ts.isTouched) {
    gfx->setCursor(0, 20);
    for (int i = 0; i < ts.touches; i++) {
      Serial.print("Touch "); Serial.print(i + 1); Serial.print(": ");;
      Serial.print("  x: "); Serial.print(ts.points[i].x);
      Serial.print("  y: "); Serial.print(ts.points[i].y);
      Serial.print("  size: "); Serial.println(ts.points[i].size);
      Serial.println(' ');

      gfx->println("X: " + String(ts.points[i].x) + "   Y: " + String(ts.points[i].y) + "   P: " + String(ts.points[i].size));
    }
    delay(100);
    gfx->fillRect(0, 20, 170, 40, BLACK);
    gfx->fillRect(0, 300, 170, 20, BLACK);
    gfx->setCursor(0, 310);
  }
  delay(1);
}
