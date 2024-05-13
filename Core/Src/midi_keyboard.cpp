/*
 * midi_keyboard.cpp
 *
 *  Created on: Sep 23, 2022
 *  edited 11.05.2024
 *      Author: scherbakov
 */

#include <midi_keyboard.h>

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv for ON
void gpioBsrr::ShLdHi_On() {
	GPIOA->BSRR = shLdHi;
}
void gpioBsrr::ShLdLo_On() {
	GPIOA->BSRR = shLdLo;
}
void gpioBsrr::ClkHi_On() {
	GPIOA->BSRR = clkHi;
}
void gpioBsrr::ClkLo_On() {
	GPIOA->BSRR = clkLo;
}
void gpioBsrr::AndHi_On() {
	GPIOA->BSRR |= andOnHi;
}
void gpioBsrr::AndLo_On() {
	GPIOA->BSRR |= andOnLo;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ for ON

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv for OFF
void gpioBsrr::ShLdHi_Off() {
	GPIOA->BSRR = shLdHi;
}
void gpioBsrr::ShLdLo_Off() {
	GPIOA->BSRR = shLdLo;
}
void gpioBsrr::ClkHi_Off() {
	GPIOA->BSRR = clkHi;
}
void gpioBsrr::ClkLo_Off() {
	GPIOA->BSRR = clkLo;
}
void gpioBsrr::AndOffHi_Off() {
	GPIOA->BSRR |= andOffHi;
}
void gpioBsrr::AndOffLo_Off() {
	GPIOA->BSRR |= andOffLo;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ for OFF

void gpioBsrr::Enable_Qre1113() {
	HAL_Delay(200);
	GPIOA->BSRR = qre1113_on1;
	HAL_Delay(200);
	GPIOA->BSRR = qre1113_on2;
	HAL_Delay(200);
}

void gpioBsrr::Disable_Qre1113() {
	HAL_Delay(200);
	GPIOA->BSRR = qre1113_off1;
	HAL_Delay(200);
	GPIOA->BSRR = qre1113_off2;
	HAL_Delay(200);
}

void gpioBsrr::Enable_BlueLed() {
	GPIOE->BSRR = blueLed_on;
}

void gpioBsrr::Disable_BlueLed() {
	GPIOE->BSRR = blueLed_off;
}

void numberS::set(cuint &channel, cuint &m) {
	number = (channel << 4) + m;
	mux = m;
	cha = channel;
}

void Keys::numberNoteSetter() {
	uint zz = 21;
	for (uint i = 0; i < sensors;) {
		notes[i] = zz;
		notes[i + 1] = zz;
		++zz;
		i += 2;
	}
}

void Keys::initBitMask() {
	numberNoteSetter();
	for (uint s = 0; s < sizeMux; s += 2) {
		bitsMidiOn[s].set();
		bitsMidiOn[s + 1].set();

		bitsMidiOff[s].reset();
		bitsMidiOff[s + 1].set();
	}
	bitsMidiOff[1].reset(0); //две нижние клавиши без механики
	bitsMidiOff[3].reset(0);
	HAL_Delay(30);
}

void Keys::wheel() {
	gpio.AndOffHi_Off(); // чтобы не грелись микрухи управляющие "off" ??
	initBitMask();
	mux.setSizeMux(sizeM);
	__HAL_TIM_SET_COUNTER(&htim3, 32760);
	gpio.Enable_Qre1113();
//	SysTick->CTRL = 0;
	print(6, 0, 60, 19, 16, divisible);
	print(6, 20, 60, 19, 16, offset);
	if (prePressure) {
		printString(6, 40, 150, 19, 16, "prePressure ON");
	} else {
		printString(6, 40, 150, 19, 16, "prePressure OFF");
	}

	while (1) {
		midiOnOrOff = OnOrOff::midiOn;
		for (uint i = 0; i < 29; ++i) {
			maskLoadMidiOn();
			gpio.ShLdHi_On();
			gpio.AndLo_On();
			gpio.ShLdLo_On();
			gpio.AndHi_On();
			gpio.AndHi_On(); // для стабильности
			mux.toggle();

			for (uint o = one; o < sizeMux; ++o) {
				maskLoadMidiOn();
				gpio.ClkLo_On();
				gpio.AndLo_On();
				gpio.ClkHi_On();
				gpio.AndHi_On();
				mux.toggle();
			}
			check();
		}
		midiOnOrOff = OnOrOff::midiOff;
		maskLoadMidiOff();
		gpio.ShLdHi_Off();
		gpio.AndOffLo_Off();
		gpio.ShLdLo_Off();
		gpio.AndOffHi_Off();
		gpio.AndOffHi_Off(); // для стабильности
		mux.toggle();

		for (uint p = one; p < sizeMux; ++p) {
			maskLoadMidiOff();
			gpio.ClkLo_Off();
			gpio.AndOffLo_Off();
			gpio.ClkHi_Off();
			gpio.AndOffHi_Off();
			mux.toggle();
		}
		check();
	}
}

void Keys::maskLoadMidiOn() {
	EXTI->IMR1 = bitsMidiOn[mux.get()].to_ulong();
}

void Keys::maskLoadMidiOff() {
	EXTI->IMR1 = bitsMidiOff[mux.get()].to_ulong();
}

void Keys::check() {
	if (!dequeOn.empty()) {
		auto &f = dequeOn.front();
		if (TIM2->CNT - timer[f.number] > timeToCleanUp) {
			bitsMidiOn[f.mux].set(f.cha);
			dequeOn.pop_front();
		}
	}
	if (!dequeNotes.empty()) {
		MidiSender(dequeNotes, bufNotes);
	}
	if (!dequeLed.empty()) {
		auto &l = dequeLed.front();
		if (TIM2->CNT - l > 200'000) {
			gpio.Disable_BlueLed();
			dequeLed.pop_front();
		}
	}
	if ((GPIOC->IDR & GPIO_PIN_4) == 0x00U) {
		HAL_Delay(200);
		displayOperations();
	}
}

void Keys::interrupt(cuint &channel) {
	numberS nu;
	nu.set(channel, mux.get());
	if (midiOnOrOff == OnOrOff::midiOn) {
		bitsMidiOn[nu.mux].reset(channel);
		dequeOn.push_back(nu);
		timerSave(nu);
	} else {
		if (nu.mux % 2 == 0) {
			sendMidi(nu.number, off_hi, 0, midiOnOrOff);
			bitsMidiOff[nu.mux + 1].set(channel);
			bitsMidiOff[nu.mux].reset(channel);
		} else {
			if (prePressure) {
				OnOrOff O = OnOrOff::midiOn;
				sendMidi(nu.number, off_lo, 0, O);
			}
			bitsMidiOff[nu.mux - 1].set(channel);
			bitsMidiOff[nu.mux].reset(channel);
		}
	}
}

void Keys::timerSave(const numberS &nu) {
	auto Now = TIM2->CNT;
	if (nu.mux % 2 == 0) {
		timer[nu.number] = Now;
	} else {
		auto time = Now - timer[nu.number - 1];
		timer[nu.number] = Now;
		sendMidi(nu.number, time, offset, midiOnOrOff);
		bitsMidiOff[nu.mux - 1].set(nu.cha);
	}
}

void Keys::sendMidi(cuint &nu, cuint &t, const int &ofs, OnOrOff &mO) {
	cuint midi_speed = divisible / t;	//~480-25000
	cuint midi_hi = midi_speed / maxMidi;
	cuint midi_lo = midi_speed - midi_hi * maxMidi;
	int m_h_o = ((int)midi_hi) + ofs;
	if (mO == OnOrOff::midiOn) {
//		test1 = SysTick->VAL; //for test
//		ST7735_LCD_Driver.FillRect(&st7735_pObj, 6, 60, 100, 20, BLACK);	//
//		print(0, 0, 159, 19, 12, t);
//		print(0, 13, 159, 19, 12, midi_speed);
//		print(0, 26, 159, 19, 12, midi_hi);
//		print(30, 26, 159, 19, 12, midi_lo);
//		print(6, 60, 159, 19, 12, test2);//
//		print(30, 39, 159, 19, 12, test2);
//		print(60, 39, 159, 19, 12, test4);
//		print(0, 52, 159, 19, 12, test3);
//		GPIOA->BSRR = 0x8000; //for test
//		GPIOA->BSRR = 0x80000000; // for test
//		GPIOA->BSRR = 0x200; //for test
//		GPIOA->BSRR = 0x2000000; //for test
	}

	if (m_h_o > 127) {
		m_h_o = 127;
		gpio.Enable_BlueLed();
		dequeLed.push_back(TIM2->CNT);
	}
	if (m_h_o < 1) {
		m_h_o = 1;
		gpio.Enable_BlueLed();
		dequeLed.push_back(TIM2->CNT);
	}
	dequeNotes.push_back( { m_h_o, midi_lo, notes[nu], mO });
}

void Keys::displayOperations() {

	int e = 0;
	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, 0x2222);
	print(6, 0, 60, 19, 16, divisible);
	print(6, 20, 60, 19, 16, offset);
	if (prePressure) {
		printString(6, 40, 150, 19, 16, "prePressure ON");
	} else {
		printString(6, 40, 150, 19, 16, "prePressure OFF");
	}
	cC = pC = __HAL_TIM_GET_COUNTER(&htim3) / 2;
	int t = TIM2->CNT;

	while (TIM2->CNT - t < 3000000) {
		if (e == 0) {
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, 0x2222);
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 6, 3, 3,
			RED);
			print(6, 0, 60, 19, 16, divisible);
			print(6, 20, 60, 19, 16, offset);
			if (prePressure) {
				printString(6, 40, 150, 19, 16, "prePressure ON");
			} else {
				printString(6, 40, 150, 19, 16, "prePressure OFF");
			}
			t = TIM2->CNT;
			while (TIM2->CNT - t < 3000000) {
				cC = __HAL_TIM_GET_COUNTER(&htim3) / 2;
				if (cC != pC) {
					t = TIM2->CNT;
					if (cC < pC) {
						divisible -= 100000;
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
								0x2222);
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 6, 3, 3,
						RED);
						print(6, 0, 60, 19, 16, divisible);
						print(6, 20, 60, 19, 16, offset);
						if (prePressure) {
							printString(6, 40, 150, 19, 16, "prePressure ON");
						} else {
							printString(6, 40, 150, 19, 16, "prePressure OFF");
						}
					} else {
						divisible += 100000;
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
								0x2222);
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 6, 3, 3,
						RED);
						print(6, 0, 60, 19, 16, divisible);
						print(6, 20, 60, 19, 16, offset);
						if (prePressure) {
							printString(6, 40, 150, 19, 16, "prePressure ON");
						} else {
							printString(6, 40, 150, 19, 16, "prePressure OFF");
						}
					}
					pC = cC;
				}
				if ((GPIOC->IDR & GPIO_PIN_4) == 0x00U) {
					HAL_Delay(300);
					++e;
					break;
				}
			}
		}

		if (e == 1) {
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, 0x2222);
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 26, 3, 3,
			RED);
			print(6, 0, 60, 19, 16, divisible);
			print(6, 20, 60, 19, 16, offset);
			if (prePressure) {
				printString(6, 40, 150, 19, 16, "prePressure ON");
			} else {
				printString(6, 40, 150, 19, 16, "prePressure OFF");
			}
			t = TIM2->CNT;
			while (TIM2->CNT - t < 3000000) {
				cC = __HAL_TIM_GET_COUNTER(&htim3) / 2;
				if (cC != pC) {
					t = TIM2->CNT;
					if (cC < pC) {
						--offset;
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
								0x2222);
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 26, 3, 3,
						RED);
						print(6, 0, 60, 19, 16, divisible);
						print(6, 20, 60, 19, 16, offset);
						if (prePressure) {
							printString(6, 40, 150, 19, 16, "prePressure ON");
						} else {
							printString(6, 40, 150, 19, 16, "prePressure OFF");
						}
					} else {
						++offset;
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
								0x2222);
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 26, 3, 3,
						RED);
						print(6, 0, 60, 19, 16, divisible);
						print(6, 20, 60, 19, 16, offset);
						if (prePressure) {
							printString(6, 40, 150, 19, 16, "prePressure ON");
						} else {
							printString(6, 40, 150, 19, 16, "prePressure OFF");
						}
					}
					pC = cC;
				}
				if ((GPIOC->IDR & GPIO_PIN_4) == 0x00U) {
					HAL_Delay(300);
					++e;
					break;
				}
			}
		}

		if (e == 2) {
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, 0x2222);
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 46, 3, 3,
			RED);
			print(6, 0, 60, 19, 16, divisible);
			print(6, 20, 60, 19, 16, offset);
			if (prePressure) {
				printString(6, 40, 150, 19, 16, "prePressure ON");
			} else {
				printString(6, 40, 150, 19, 16, "prePressure OFF");
			}
			t = TIM2->CNT;
			while (TIM2->CNT - t < 3000000) {
				cC = __HAL_TIM_GET_COUNTER(&htim3) / 2;
				if (cC != pC) {
					t = TIM2->CNT;
					if (cC < pC) {
						prePressure = 0;
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
								0x2222);
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 46, 3, 3,
						RED);
						print(6, 0, 60, 19, 16, divisible);
						print(6, 20, 60, 19, 16, offset);
						printString(6, 40, 150, 19, 16, "prePressure OFF");
					} else {
						prePressure = 1;
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
								0x2222);
						ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 46, 3, 3,
						RED);
						print(6, 0, 60, 19, 16, divisible);
						print(6, 20, 60, 19, 16, offset);
						printString(6, 40, 150, 19, 16, "prePressure ON");
					}
					pC = cC;
				}
				if ((GPIOC->IDR & GPIO_PIN_4) == 0x00U) {
					HAL_Delay(300);
					++e;
					break;
				}
			}
		}

		if (e == 3) {
			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, 0x3333);
			printString(40, 35, 80, 20, 16, "OFF....??");
			cC = pC = __HAL_TIM_GET_COUNTER(&htim3) / 2;
			t = TIM2->CNT;
			while (TIM2->CNT - t < 3000000) {
				cC = __HAL_TIM_GET_COUNTER(&htim3) / 2;
				if (cC != pC) {
					t = TIM2->CNT;
					ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79,
							0x3333);
					printString(40, 35, 80, 20, 16, "SLEEP....");
					pC = cC;
					gpio.Disable_Qre1113();
					HAL_Delay(500);
					HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN4); //pin4 == кнопка К1 на плате
					__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
					HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4);
					HAL_PWR_EnterSTANDBYMode();
				}
				if ((GPIOC->IDR & GPIO_PIN_4) == 0x00U) {
					HAL_Delay(300);
					++e;
					break;
				}
			}
		}
		if (e > 2) {
			e = 0;
		} else {
			++e;
		}
	}	//while

	timeToCleanUp = uint(float(divisible) / 1.1f / 127.0f);
//	max = divisible / (maxMidi * maxMidi);
	off_lo = uint(float(divisible) / 1.0f / 127.0f);
	off_hi = uint(float(divisible) / 60.0f / 127.0f);

	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, 159, 79, BLACK);
	print(6, 0, 60, 19, 16, divisible);
	print(6, 20, 60, 19, 16, offset);
	if (prePressure) {
		printString(6, 40, 150, 19, 16, "prePressure ON");
	} else {
		printString(6, 40, 150, 19, 16, "prePressure OFF");
	}
}

void Keys::print(cuint x, cuint y, cuint width, cuint height, cuint size,
		const int value) {
	const std::string u = std::to_string(value);
	LCD_ShowString(x, y, width, height, size, (int8_t*) u.c_str());
}

void Keys::print(cuint x, cuint y, cuint width, cuint height, cuint size,
		uint value) {
	const std::string u = std::to_string(value);
	LCD_ShowString(x, y, width, height, size, (int8_t*) u.c_str());
}

void Keys::printString(cuint x, cuint y, cuint width, cuint height, cuint size,
		const std::string value) {
	LCD_ShowString(x, y, width, height, size, (int8_t*) value.c_str());
}

void muxer::toggle() {
	if (mux < size - 1) {
		++mux;
	} else {
		mux = 0;
	}
}

uint muxer::get() const {
	return mux;
}

void muxer::setSizeMux(cuint &s) {
	size = s;
}
