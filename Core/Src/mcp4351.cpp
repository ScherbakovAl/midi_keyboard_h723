#include "mcp4351.h"

void printString(cuint x, cuint y, cuint width, cuint height, cuint size,
		const std::string value) {
	LCD_ShowString(x, y, width, height, size, (int8_t*) value.c_str());
}

#define ADS1115_ADDRESS 0x48
unsigned char ADSwrite[6];
int16_t reading = 0;
float voltage = 0.0f;
const float voltageConv = 6.144f / 32768.0f;

void mcp_testing() {
	int qwe = 0;
	int x = 1;
	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 79, 159, BLACK);

	//datasheet pg51 Device commands

	//AAAACCDD (address:Command:top two Data bits)// command 00 = write; 10 = read

//#define POT_3 0b01110000   //wiper 3 is at address 7// datasheet page 40
//#define POT_2 0b01100000   //wiper 2 is at address 6
//#define POT_1 0b00010000   // wiper 1 is at address 1
//#define POT_0 0b00000000   //wiper 0 is at address 0.

//#define TCON0 0b01000000  //address 0x04
//#define TCON1 0b10100000 //address 0x0A

//write 0b11111111 to TCON0 will connect resistor ends and wiper of first two pots

//write 0b11111111 to TCON1 will connect resistor ends and wiper of next two pots

//SPI protocol for this device requires 16 bit write. First the 8-bit pot address and then the 7 bits of data.

//wirteSPI_16bit(POT0, data)

//Example

//Set up potentiometer

//	WriteSPI_16bit(TCON0, 0b11111111);
//	WriteSPI_16bit(TCON1, 0b11111111);

//write data to move wiper

	WriteSPI_16bit(POT_0, data); //data 0 - 127 or 0 - 255 if 8-bit device

	uint8_t spi_data1[2] = { 0x01, 54 };
	HAL_SPI_Transmit(&hspi2, spi_data1, 2, 0xff);

	while (1) {
		print(20, 140, 30, 8, 12, qwe);
		pinMultiplexer(x);
		print(0, x * 12, 10, 12, 12, x);
		print(20, x * 12, 40, 12, 12, ADSread());
		if (x < 8) {
			x++;
		} else {
			x = 1;
			qwe++;
		}
		HAL_Delay(30);
	}
}

float ADSread() {
	ADSwrite[0] = 0x01;
	ADSwrite[1] = 0xD1; //C1 - 1, D1 - 2...
	ADSwrite[2] = 0x83;
	HAL_I2C_Master_Transmit(&hi2c3, ADS1115_ADDRESS << 1, ADSwrite, 3, 10);
	ADSwrite[0] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c3, ADS1115_ADDRESS << 1, ADSwrite, 1, 10);
	HAL_I2C_Master_Receive(&hi2c3, ADS1115_ADDRESS << 1, ADSwrite, 2, 10);
	reading = (ADSwrite[0] << 8 | ADSwrite[1]);
	if (reading < 0) {
		reading = 0;
	}
	return reading * voltageConv;

}

void pinMultiplexer(int a) {
	GPIOC->BSRR = 0x80;
	(a & (1 << 0)) ? GPIOE->BSRR = 0x200 : GPIOE->BSRR = 0x2000000;
	(a & (1 << 1)) ? GPIOE->BSRR = 0x80 : GPIOE->BSRR = 0x800000;
	(a & (1 << 2)) ? GPIOB->BSRR = 0x2 : GPIOB->BSRR = 0x20000;
	GPIOC->BSRR = 0x800000;
}
