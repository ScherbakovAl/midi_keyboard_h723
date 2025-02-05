#include "mcp4351.h"

void hc238_testing() {
	while (1) {
//		toggle_pB1();
//		toggle_pE7();
//		toggle_pE9();

		enable_Dipot_0();

		set_Pot_pin_0(1);
		set_Pot_pin_1(255);
		set_Pot_pin_2(1);
		set_Pot_pin_3(255);

		enable_Dipot_1();

		set_Pot_pin_0(1);
		set_Pot_pin_1(255);
		set_Pot_pin_2(1);
		set_Pot_pin_3(255);

//		int i = 0;
//		int x = 0;
//		enable_Dipot_1();

		while (1) {
//			toggle_pB1();

//			++x;
//			if(x == 30000){
//			set_Pot_pin_3(i++);
//			if(i == 255) i = 0;
//			x = 0;
//			}

//			on_pE9();
			Multiplexer_Pin(0);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();

//			on_pE9();
			Multiplexer_Pin(1);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();

//			on_pE9();
			Multiplexer_Pin(2);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();

//			on_pE9();
			Multiplexer_Pin(3);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();
//			toggle_pB1();

			toggle_pB1();

//			on_pE9();
			Multiplexer_Pin(4);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();

//			on_pE9();
			Multiplexer_Pin(5);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();

//			on_pE9();
			Multiplexer_Pin(6);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();

//			on_pE9();
			Multiplexer_Pin(7);
//			off_pE9();
//			HAL_Delay(1);
			toggle_pE7();
			toggle_pE9();
//			toggle_pE7();
//			toggle_pE9();
		}
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
	GPIOC->BSRR = 0x800200; // pC7 - off, pC9 - on
	HAL_Delay(1);
}
void enable_Dipot_1() {
	GPIOC->BSRR = 0x2000080; // pC7 - on, pC9 - off
	HAL_Delay(1);
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

void toggle_pB1() {
	GPIOB->BSRR = 0x2;
	GPIOB->BSRR = 0x20000;
}
void toggle_pE7() {
	GPIOE->BSRR = 0x80;
	GPIOE->BSRR = 0x800000;
}
void toggle_pE9() {
	GPIOE->BSRR = 0x200;
	GPIOE->BSRR = 0x2000000;
}

void on_pE9(){
	GPIOE->BSRR = 0x200;
}

void off_pE9(){
	GPIOE->BSRR = 0x2000000;
}
