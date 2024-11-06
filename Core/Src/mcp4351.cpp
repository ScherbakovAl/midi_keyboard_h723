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
	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, BLACK);

	while (1) {
		print(6, 0, 60, 19, 12, qwe);
		qwe++;
		print(6, 12, 60, 19, 12, ADSread());
		HAL_Delay(300);
	}
}

float ADSread(){
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
