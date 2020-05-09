#include <SPI.h>
#pragma once
#define COMMAND_1 0b00000000
#define COMMAND_2 0b01000000
#define COMMAND_3 0b11000000
#define COMMAND_4 0b10000000
//parameters COMMAND_1
#define DIG8_SEG20 0b0000
#define DIG9_SEG19 0b1000
#define DIG10_SEG18 0b1001
#define DIG11_SEG17 0b1010
#define DIG12_SEG16 0b1011
#define DIG13_SEG15 0b1100
#define DIG14_SEG14 0b1101
#define DIG15_SEG13 0b1110
#define DIG16_SEG12 0b1111
//parameters COMMAND_2
#define NORMAL_OPERATION_MODE 0b0000
#define TEST_MODE 0b1000
#define INCREMENT_ADDRESS 0b000
#define FIXED_ADDRESS 0b100
#define WRITE_DATA_TO_DISPLAY_MODE 0b00
#define WRITE_DATA_TO_LED_PORT 0b01
#define READ_KEY_DATA 0b10
#define READ_SW_DATA 0b11
//parameters COMMAND_4
#define DISPLAY_ON 0b1000
#define DISPLAY_OFF 0b0000
#define PULSE_WIDTH1 0b000
#define PULSE_WIDTH2 0b001
#define PULSE_WIDTH4 0b010
#define PULSE_WIDTH10 0b011
#define PULSE_WIDTH11 0b100
#define PULSE_WIDTH12 0b101
#define PULSE_WIDTH13 0b110
#define PULSE_WIDTH14 0b111

class pt6311{
  private:
    const int spi_timeout = 25;
    int CS;
    int numOfDigit;
    int displayState;
    int displayBrighthess;
    int buf[16];
    void SendByte(byte data);
  public:
    short int symbolList[512];
    pt6311(int CS_pin, int num_Of_Digit);
    void setBrightness(int br); // from 0 to 7
    void displayOn();
    void displayOff();
    int getBrightness(); //return brightness
    bool getState(); // return on or off
    void setDigit(int pos, char _data); // pos from 0 to numOfDigit
};
