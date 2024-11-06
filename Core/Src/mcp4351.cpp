#include "mcp4351.h"

void printString(cuint x, cuint y, cuint width, cuint height, cuint size,
		const std::string value) {
	LCD_ShowString(x, y, width, height, size, (int8_t*) value.c_str());
}

void mcp_testing() {
	__disable_irq();
	int qwe = 0;
	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, BLACK);
	while (1) {
		print(6, 0, 60, 19, 16, qwe);
		qwe++;
	}
}
