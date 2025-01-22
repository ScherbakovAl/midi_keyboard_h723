#include "mcp4351.h"

void hc238_testing() {
	while (1) {
		enable_Dipot_0();
		Multiplexer_Pin(0);
		Multiplexer_Pin(1);
		Multiplexer_Pin(2);
		Multiplexer_Pin(3);
		Multiplexer_Pin(4);
		Multiplexer_Pin(5);
		Multiplexer_Pin(6);
		Multiplexer_Pin(7);
		enable_Dipot_1();
	}
}

//B3 - A0, B5 - A1, B7 - A2
int pins[8] = { 0xA80000, 0xA00008, 0x880020, 0x800028, 0x280080, 0x200088,
		0x800A0, 0xA8 };

void Multiplexer_Pin(int p) {
	GPIOB->BSRR = pins[p];
}

// data to Dipot_0 or Dipot_1
void enable_Dipot_0() {
	GPIOC->BSRR = 0x2000080; // pC7 - on, pC9 - off
}
void enable_Dipot_1() {
	GPIOC->BSRR = 0x800200; // pC7 - off, pC9 - on
}

// data to pin 1-2-3-4 Dipot_X
uint8_t spi_data_pot_pin_0[2] = { 0x00, 0 };
uint8_t spi_data_pot_pin_1[2] = { 0x10, 0 };
uint8_t spi_data_pot_pin_2[2] = { 0x60, 0 };
uint8_t spi_data_pot_pin_3[2] = { 0x70, 0 };

void set_Pot_pin_0(int value) {
	spi_data_pot_pin_0[1] = value;
	HAL_SPI_Transmit(&hspi2, spi_data_pot_pin_0, 2, 0xff);
}

void set_Pot_pin_1(int value) {
	spi_data_pot_pin_1[1] = value;
	HAL_SPI_Transmit(&hspi2, spi_data_pot_pin_1, 2, 0xff);
}

void set_Pot_pin_2(int value) {
	spi_data_pot_pin_2[1] = value;
	HAL_SPI_Transmit(&hspi2, spi_data_pot_pin_2, 2, 0xff);
}

void set_Pot_pin_3(int value) {
	spi_data_pot_pin_3[1] = value;
	HAL_SPI_Transmit(&hspi2, spi_data_pot_pin_3, 2, 0xff);
}
