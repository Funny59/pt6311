#include "pt6311.h"
#include <SPI.h>

pt6311::pt6311(int CS_pin, int num_Of_Digit){
  CS = CS_pin;
  numOfDigit = num_Of_Digit;
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE3);
  SendByte(COMMAND_2 | NORMAL_OPERATION_MODE | INCREMENT_ADDRESS | WRITE_DATA_TO_DISPLAY_MODE);
  digitalWrite(CS, LOW);
  SPI.transfer(COMMAND_3);
  for (int i = 0; i < 13; i++) {
    SPI.transfer(0);
    SPI.transfer(0);
    SPI.transfer(0);
  }
  digitalWrite(CS, HIGH);
  delayMicroseconds(spi_timeout);
  switch(numOfDigit){
    case 9:
      SendByte(COMMAND_1 | DIG9_SEG19);
      break;
    case 10:
      SendByte(COMMAND_1 | DIG10_SEG18);
      break;
    case 11:
      SendByte(COMMAND_1 | DIG11_SEG17);
      break;
    case 12:
      SendByte(COMMAND_1 | DIG12_SEG16);
      break;
    case 13:
      SendByte(COMMAND_1 | DIG13_SEG15);
      break;
    case 14:
      SendByte(COMMAND_1 | DIG14_SEG14);
      break;
    case 15:
      SendByte(COMMAND_1 | DIG15_SEG13);
      break;
    case 16:
      SendByte(COMMAND_1 | DIG16_SEG12);
      break;
    default:
      SendByte(COMMAND_1 | DIG8_SEG20);
      break;
  }
  SendByte(COMMAND_4 | DISPLAY_ON | PULSE_WIDTH14);
  displayState = DISPLAY_ON;
  displayBrighthess = PULSE_WIDTH14;
  for(int i = 0; i < 16; i++)buf[i] = 0;
};

void pt6311::setBrightness(int br){ 
      displayBrighthess = br;
      SendByte(COMMAND_4 | displayState | displayBrighthess);
    };

void pt6311::displayOn(){
  displayState = DISPLAY_ON;
  SendByte(COMMAND_4 | displayState | displayBrighthess);
}
    
void pt6311::displayOff(){
  displayState = DISPLAY_OFF;
  SendByte(COMMAND_4 | displayState | displayBrighthess);
}

int pt6311::getBrightness(){ 
  return displayBrighthess;
}

bool pt6311::getState(){ 
  return displayState>0?true:false;
}

void pt6311::setDigit(int pos, char _data){ 
  int data = symbolList[_data];
  if(buf[pos] != data){
    buf[pos] = data;
    SendByte(COMMAND_2 | NORMAL_OPERATION_MODE | WRITE_DATA_TO_DISPLAY_MODE); //cmd2
    digitalWrite(CS, LOW);
    SPI.transfer(COMMAND_3 | (pos * 0x03));
    SPI.transfer(byte(data));
    SPI.transfer(byte(data >> 8));
    SPI.transfer(byte(data >> 16));
    digitalWrite(CS, HIGH);
  }
}

void pt6311::SendByte(byte data) {
  digitalWrite(CS, LOW);
  SPI.transfer(data);
  digitalWrite(CS, HIGH);
  delayMicroseconds(spi_timeout);
}
