/*
 *  midi_keyboard.h
 *
 *  Created on: Sep 23, 2022
 *     Author: scherbakov.al
 */

#pragma once

#include "usb_device.h"
#include <deque>
#include <bitset>
#include <string>
extern "C" {
#include "lcd.h"
}

extern TIM_HandleTypeDef htim3;

using uint = unsigned int;
using cuint = const uint;

enum class OnOrOff : uint8_t {
	midiOff = 128, midiOn = 144
};

class gpioBsrr {
public:
	void ShLdHi_On();		// +A0	(+SH/LD)
	void ShLdLo_On();		// -A0	(-SH/LD)
	void ClkHi_On();		// +A1	(+CLK)
	void ClkLo_On();		// -A1	(-CLK)
	void AndHi_On();		// +A2	(AND_ON)
	void AndLo_On();		// -A2	(AND_ON)

	void ShLdHi_Off();
	void ShLdLo_Off();
	void ClkHi_Off();
	void ClkLo_Off();
	void AndOffHi_Off();		// +A3	(AND_OFF)
	void AndOffLo_Off();		// -A3	(AND_OFF)

	void Enable_Qre1113();
	void Disable_Qre1113();
	void Enable_BlueLed();
	void Disable_BlueLed();

private:
	cuint shLdHi = 0x1;
	cuint shLdLo = 0x10000;
	cuint clkHi = 0x2;
	cuint clkLo = 0x20000;
	cuint andOnHi = 0x4;
	cuint andOnLo = 0x40000;
	cuint andOffHi = 0x8;
	cuint andOffLo = 0x80000;
	cuint qre1113_on1 = 0x100000;
	cuint qre1113_on2 = 0x200000;
	cuint qre1113_off1 = 0x10;
	cuint qre1113_off2 = 0x20;
	cuint blueLed_on = 0x8;
	cuint blueLed_off = 0x80000;
};

class numberS {
public:
	void set(cuint &channel, cuint &m);
	uint number = 0;
	uint mux = 0;
	uint cha = 0;
};

class Note {
public:
	const int hi = 0;
	cuint lo = 0;
	cuint note = 0;
	OnOrOff mO = OnOrOff::midiOn;
};

class muxer {
public:
	void toggle();
	uint get() const;
	void setSizeMux(cuint &s);
private:
	uint mux = 0;
	uint size;
};

class Keys {
public:
	void wheel();
	void interrupt(cuint &channel);
	template<typename T>
	void print(cuint x, cuint y, cuint width, cuint height, cuint size,
			T value) {
		const std::string u = std::to_string(value);
		LCD_ShowString(x, y, width, height, size, (int8_t*) u.c_str());
	}
	void printString(cuint x, cuint y, cuint width, cuint height, cuint size,
			const std::string value);
private:
	void numberNoteSetter();
	void initBitMask();
	void maskLoadMidiOn();
	void maskLoadMidiOff();
	void check();
	void timerSave(const numberS &nu);
	void sendMidi(cuint &nu, cuint &t, const int &ofS, OnOrOff &mO);
	void displayOperations();
	void printMenu(uint background);
	void SaveToMemory();
	void MemoryRead();
	int checkMemory();

	cuint KeyMemoryTest = 123456;
	cuint Flash_Address = 0x08040000;
	volatile uint Data[8] = { };
	uint DataRead[8] = { };
	static cuint sensors = 176;
	static cuint channelBits = 11;
	static cuint sizeMux = 16;
	cuint sizeM = sizeMux;
	cuint maxMidi = 127;
	uint divisible = 7'900'000;
	uint timeToCleanUp = uint(float(divisible) / 1.1f / 127.0f);
	uint off_lo = uint(float(divisible) / 1.0f / 127.0f);
	uint off_hi = uint(float(divisible) / 60.0f / 127.0f);
	int offset = -4;
	uint prePressure = 0;

	muxer mux;
	gpioBsrr gpio;
	OnOrOff midiOnOrOff = OnOrOff::midiOn;
	std::deque<numberS> dequeOn;
	std::deque<Note> dequeNotes;
	std::deque<uint> dequeLed;
	std::bitset<channelBits> bitsMidiOn[sizeMux];
	std::bitset<channelBits> bitsMidiOff[sizeMux];
	uint timer[sensors] = { };
	uint notes[sensors];
	uint8_t bufNotes[512] = { };
	static cuint zero = 0;
	static cuint one = 1;
	static cuint two = 2;

	//vvvvvvvvvvvvvvvvvv display
	uint lineNumber = 0;
	int cC = 0;
	int pC = 0;
};
