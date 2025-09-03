#include <Arduino.h>
#include "chip_info.h"
#include "WS_Matrix.h"
// English: Please note that the brightness of the lamp bead should not be too high, which can easily cause the temperature of the board to rise rapidly, thus damaging the board !!!
// Chinese: 请注意，灯珠亮度不要太高，容易导致板子温度急速上升，从而损坏板子!!!
void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(300);

  GetPrintChipInfo();
  Serial.println(); 

  Serial.println("Free heap memory: " + String(esp_get_free_heap_size()) + " bytes");

  multi_heap_info_t info;
  heap_caps_get_info(&info, MALLOC_CAP_INTERNAL); // internal RAM
  /*
  info.total_free_bytes;   // total currently free in all non-continues blocks
  info.minimum_free_bytes;  // minimum free ever
  info.largest_free_block;   // largest continues block to allocate big array
  */
  Serial.println();
  Serial.println("INTERNAL RAM:");
  Serial.println("Total available memory: " + String(info.total_free_bytes) + " bytes");
  Serial.println("Largest available block: " + String(info.largest_free_block) + " bytes");
  Serial.println("Minimum free ever: " + String(info.minimum_free_bytes) + " bytes");   

  heap_caps_get_info(&info, MALLOC_CAP_SPIRAM);
  /*
  info.total_free_bytes;   // total currently free in all non-continues blocks
  info.minimum_free_bytes;  // minimum free ever
  info.largest_free_block;   // largest continues block to allocate big array
  */
  Serial.println();
  Serial.println("SPI RAM:");
  Serial.println("Total available memory: " + String(info.total_free_bytes) + " bytes");
  Serial.println("Largest available block: " + String(info.largest_free_block) + " bytes");
  Serial.println("Minimum free ever: " + String(info.minimum_free_bytes) + " bytes");   


  Matrix_Init();
}
int x=0;

void loop()
{
  RGB_Matrix1(x);
  delay(40);
  x++;
  if(x==24)
    x=0;
  
}
