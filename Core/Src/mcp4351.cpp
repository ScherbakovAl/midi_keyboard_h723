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

	uint8_t spi_data1[2] = {0x01,0x00};
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
