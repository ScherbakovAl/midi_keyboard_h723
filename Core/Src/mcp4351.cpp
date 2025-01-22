#include "mcp4351.h"

void mcp_testing() {
	int qwe = 0;

	int aa = 0;
	int bb = 0;
	int cc = 0;
	int dd = 0;

	while (1) {
		for (int x = 0; x < 8; ++x) {
			pinMultiplexer(x);

		}
		qwe++;

		if (aa < 250) {
			aa += 1;
		} else {
			aa = 0;
		}

		setPot(0, aa);
//		setPot(1, bb);
//		setPot(2, cc);
//		setPot(3, dd);
	}
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
