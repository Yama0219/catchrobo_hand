//
// Created by kenke on 2023/08/06.
//

#ifndef SERIAL_SERVO_TEST_STS3215_H
#define SERIAL_SERVO_TEST_STS3215_H

#include "main.h"

void step_control(UART_HandleTypeDef *huart, uint8_t ID, uint16_t pos, uint16_t time, uint16_t speed);
void read_address(UART_HandleTypeDef *huart, uint8_t ID, uint8_t register_address, uint8_t read_byte);

void lock_EEPROM(UART_HandleTypeDef *huart, uint8_t ID);
void unlock_EEPROM(UART_HandleTypeDef *huart, uint8_t ID);

void set_ID(UART_HandleTypeDef *huart, uint8_t ID, uint8_t NEW_ID);
#endif //SERIAL_SERVO_TEST_STS3215_H
