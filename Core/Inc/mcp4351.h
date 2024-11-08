#pragma once

#include "stm32h7xx_hal.h"
#include "i2c.h"
#include "spi.h"
#include <string>

extern "C" {
#include "lcd.h"
}

using uint = unsigned int;
using cuint = const uint;

void mcp_testing();

float ADSread();

template<typename T>
void print(cuint x, cuint y, cuint width, cuint height, cuint size, T value){
	const std::string u = std::to_string(value);
	LCD_ShowString(x, y, width, height, size, (int8_t*) u.c_str());
}

void printString(cuint x, cuint y, cuint width, cuint height, cuint size,
		const std::string value);

void pinMultiplexer(int a);

void setPot(int pot, int value);
