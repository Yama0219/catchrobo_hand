//
// Created by kenke on 2023/08/06.
//

#include "STS3215.h"
#include "main.h"



void step_control(UART_HandleTypeDef *huart, uint8_t ID, uint16_t pos, uint16_t time, uint16_t speed) {
  uint8_t message[13];

  message[0] = 0xFF;
  message[1] = 0xFF;
  message[2] = ID;
  message[3] = 0x09;
  message[4] = 0x03;
  message[5] = 0x2A;
  message[6] = pos & 0xFF;
  message[7] = pos >> 8;
  message[8] = time & 0xFF;
  message[9] = time >> 8;
  message[10] = speed & 0xFF;
  message[11] = speed >> 8;

  int sum = 0;
  for (int i = 2; i < 12; i++) {
    sum += message[i];
  }

  message[12] = ~(sum & 0xFF);
  HAL_UART_Transmit(huart, message, 13, 1);
}

void set_ID(UART_HandleTypeDef *huart, uint8_t ID, uint8_t NEW_ID) {
  unlock_EEPROM(huart, ID);
  uint8_t message[8];

  message[0] = 0xFF;
  message[1] = 0xFF;
  message[2] = ID;
  message[3] = 0x04;
  message[4] = 0x03;
  message[5] = 0x05;
  message[6] = NEW_ID;

  int sum = 0;
  for (int i = 2; i < 7; i++) {
    sum += message[i];
  }

  message[7] = ~(sum & 0xFF);
  HAL_UART_Transmit(huart, message, 8, 1);

  lock_EEPROM(huart, NEW_ID);
}

void read_address(UART_HandleTypeDef *huart, uint8_t ID, uint8_t register_address, uint8_t read_byte) {
  uint8_t message[8];

  message[0] = 0xFF;
  message[1] = 0xFF;
  message[2] = ID;
  message[3] = 0x04;
  message[4] = 0x02;
  message[5] = register_address;
  message[6] = read_byte;

  int sum = 0;
  for (int i = 2; i < 7; i++) {
    sum += message[i];
  }

  message[7] = ~(sum & 0xFF);
  HAL_UART_Transmit(huart, message, 8, 1);

}

void unlock_EEPROM(UART_HandleTypeDef *huart, uint8_t ID) {
  uint8_t message[8];

  message[0] = 0xFF;
  message[1] = 0xFF;
  message[2] = ID;
  message[3] = 0x04;
  message[4] = 0x03;
  message[5] = 0x37;
  message[6] = 0x00;

  int sum = 0;
  for (int i = 2; i < 7; i++) {
    sum += message[i];
  }

  message[7] = ~(sum & 0xFF);
  HAL_UART_Transmit(huart, message, 8, 1);
}
void lock_EEPROM(UART_HandleTypeDef *huart, uint8_t ID) {
  uint8_t message[8];

  message[0] = 0xFF;
  message[1] = 0xFF;
  message[2] = ID;
  message[3] = 0x04;
  message[4] = 0x03;
  message[5] = 0x37;
  message[6] = 0x01;

  int sum = 0;
  for (int i = 2; i < 7; i++) {
    sum += message[i];
  }

  message[7] = ~(sum & 0xFF);
  HAL_UART_Transmit(huart, message, 8, 1);
}