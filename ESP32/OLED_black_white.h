
// ************ Hardware definitions *********************

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//#define OLED_SPI
  #define OLED_CLK   19
  #define OLED_MOSI  18
  #define OLED_DC    17
  #define OLED_CS    16
//  #define OLED_RESET  5
  #define OLED_MISO   4  // not used, must be defined for hardware SPI
  #define OLED_HARDWARE_SPI  // daefault is VSPI on ESP32

#define OLED_I2C
/*  
  // bela plata  // Start I2C Communication SDA = 4 and SCL = 15
  // https://www.aliexpress.com/item/32847022581.html
  // Heltec ESP32 Oled Wifi kit 32
  #define OLED_RESET     16 // Reset pin # (or -1 if sharing Arduino reset pin)
  #define OLED_SCL       15
  #define OLED_SDA        4
*/  
  // črna plata // https://www.aliexpress.com/item/4000065217965.html
  #define OLED_RESET     -1
  #define OLED_SCL        4
  #define OLED_SDA        5

  #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

