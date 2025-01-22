#pragma once

#include "stm32h7xx_hal.h"
#include "spi.h"
#include <string>

extern "C" {
#include "lcd.h"
}

using uint = unsigned int;
using cuint = const uint;

void hc238_testing();

void Multiplexer_Pin(int p);

void enable_Dipot_0();
void enable_Dipot_1();

void set_Pot_pin_0(int value);
void set_Pot_pin_1(int value);
void set_Pot_pin_2(int value);
void set_Pot_pin_3(int value);
