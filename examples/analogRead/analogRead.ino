/*
  ReadAnalogVoltage

  Reads an analog input off channel0, converts it to voltage, and prints the
  result to the Serial Monitor. Attach the center pin of a potentiometer to pin
  A0, and the outside pins to +3V3 and ground.

  This example code is in the public domain.
*/

#include "MCP3x6x.h"

MCP3561 mcp;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

#if defined ARDUINO_AVR_PROMICRO8
  if (!mcp.begin(10))
#elif defined ARDUINO_GRAND_CENTRAL_M4
  SPIClass mySPI = SPIClass(&sercom5, 125, 126, 99, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2);
  if (!mcp.begin(SS, &mySPI))
//#elif
// todo: might need further cases, didn't check for all boards
#else
  if (!mcp.begin())
#endif
  {
    // failed to initialize
    while (1)
      ;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on default analog channel:
  int32_t adcdata = mcp.analogRead(0);
  // Convert the analog reading (which goes from 0 - 2^24) to a voltage (0 - 3V3):
  double voltage = adcdata * (3.3 / (pow(2, 24) - 1));
  // print out the value you read:
  Serial.println(voltage, 10);
  // pause program for one second
  delay(1000);
}
