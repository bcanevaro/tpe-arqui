#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

uint8_t rtc_hours();
uint8_t rtc_minutes();
uint8_t rtc_seconds();
void rtc_bd_to_binary();
uint8_t get_key();
uint8_t kb_flag();
uint8_t read_port();
uint8_t rtc_day();
uint8_t rtc_month();
uint8_t rtc_year();
#endif