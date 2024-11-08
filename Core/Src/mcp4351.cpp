#include "mcp4351.h"

void mcp_testing() {
	int qwe = 0;
	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 79, 159, BLACK);

	int aa = 0;
	int bb = 0;
	int cc = 0;
	int dd = 0;

	while (1) {
		for (int x = 0; x < 8; ++x) {
			pinMultiplexer(x);
			print(20, 140, 30, 8, 12, qwe);
			print(0, x * 12, 10, 12, 12, x);
			HAL_Delay(30);
			print(20, x * 12, 20, 12, 12, ADSread());
		}
		qwe++;

		if (aa < 250) {
			aa += 1;
		} else {
			aa = 0;
		}

		if (bb < 250) {
			bb += 10;
		} else {
			bb = 0;
		}

		if (cc < 250) {
			cc += 20;
		} else {
			cc = 0;
		}

		if (dd < 250) {
			dd += 50;
		} else {
			dd = 0;
		}
		setPot(0, aa);
		setPot(1, bb);
		setPot(2, cc);
		setPot(3, dd);
	}
}

void printString(cuint x, cuint y, cuint width, cuint height, cuint size,
		const std::string value) {
	LCD_ShowString(x, y, width, height, size, (int8_t*) value.c_str());
}

float ADSread() {
	unsigned char ADSwrite[6];
	int16_t reading = 0;
	const float voltageConv = 6.144f / 32768.0f;
	ADSwrite[0] = 0x01;
	ADSwrite[1] = 0xD1; //C1 - 1, D1 - 2...
	ADSwrite[2] = 0x83;
	HAL_I2C_Master_Transmit(&hi2c3, 0x48 << 1, ADSwrite, 3, 10);
	ADSwrite[0] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c3, 0x48 << 1, ADSwrite, 1, 10);
	HAL_I2C_Master_Receive(&hi2c3, 0x48 << 1, ADSwrite, 2, 10);
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

void setPot(int pot, int value) {
	uint8_t spi_data1[2];
	if (pot == 0) {
		spi_data1[0] = 0x00; //0й
	} else if (pot == 1) {
		spi_data1[0] = 0x10; //1й
	} else if (pot == 2) {
		spi_data1[0] = 0x60; //2й
	} else if (pot == 3) {
		spi_data1[0] = 0x70; //3й
	}
	spi_data1[1] = value;
	HAL_SPI_Transmit(&hspi2, spi_data1, 2, 0xff);
}
