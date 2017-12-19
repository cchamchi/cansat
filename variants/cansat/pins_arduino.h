// CANSAT : ATMEGA128  // 
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
// ATmega128 has A0 ~ G4 = 6*8+5 = 48+5 = 53..

#define NUM_DIGITAL_PINS            54
#define NUM_ANALOG_INPUTS			8
#define FIRST_ANALOG_PIN            050
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + FIRST_ANALOG_PIN : -1)

#define digitalPinHasPWM(p)         (((p) >= 2 && (p) <= 13) || ((p) >= 44 && (p)<= 46))

static const uint8_t SS    = 010 ; // B0
static const uint8_t MOSI = 012 ; // B2
static const uint8_t MISO = 013 ; // B3
static const uint8_t SCK   = 011 ; // B1

static const uint8_t SDA  = 031 ; // D1
static const uint8_t SCL  = 030 ; // D0
//#define LED_BUILTIN 13
#define LED_BUILTIN 13

// CANSAT ANALOG PORT csPORT
static const uint8_t csA0 = 050 ; // F0
static const uint8_t csA1 = 051 ; // F1
static const uint8_t csA2 = 052 ; // F2
static const uint8_t csA3 = 053 ; // F3
static const uint8_t csA4 = 054 ; // F4
static const uint8_t csA5 = 055 ; // F5
static const uint8_t csA6 = 056 ; // F6
static const uint8_t csA7 = 057 ; // F7

// CANSAT ANALOG PORT
static const uint8_t A0 = 057 ; // F7
static const uint8_t A1 = 056 ; // F6
static const uint8_t A2 = 055 ; // F5
static const uint8_t A3 = 054 ; // F4
static const uint8_t A4 = 053 ; // F3
static const uint8_t A5 = 052 ; // F2
static const uint8_t A6 = 051 ; // F1
static const uint8_t A7 = 050 ; // F0


// CANSAT DIGITAL PORT
static const uint8_t D0 = 040 ; // A0
static const uint8_t D1 = 041 ; // A1
static const uint8_t D2 = 042 ; // A2
static const uint8_t D3 = 043 ; // A3
static const uint8_t D4 = 044 ; // A4
static const uint8_t D5 = 045 ; // A5
static const uint8_t D6 = 046 ; // A6
static const uint8_t D7 = 047 ; // A7

static const uint8_t D8  = 015 ; // B5
static const uint8_t D9  = 016 ; // B6
static const uint8_t D10 = 017 ; // B7
static const uint8_t D11 = 012 ; // B2
static const uint8_t D12 = 013 ; // B3
static const uint8_t D13 = 011 ; // B1


// CANSTA LED 
static const uint8_t LED0 = 024 ; // C4
static const uint8_t LED1 = 025 ; // C5
static const uint8_t LED2 = 026 ; // C6
static const uint8_t LED3 = 027 ; // C7

// maybe external interrupts
// need to set...
#define digitalPinToPCICR(p)    (((2 <= (p) && (p) <= 5) || \
	                             (36 <= (p) && (p) <= 39) ) ? (&PCICR) : ((uint8_t *)0))

#define digitalPinToPCICRbit(p) (((2 <= (p) && (p) <= 5) || \
	                             (36 <= (p) && (p) <= 39) ) ? 2 : 0 )

#define digitalPinToPCMSK(p)    (((2 <= (p) && (p) <= 5) || \
	                             (36 <= (p) && (p) <= 39) ) ? PCMSK2 : 0 )
// ?
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

// ?
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
	(uint16_t) &DDRE,
	(uint16_t) &DDRF,
	(uint16_t) &DDRG,
	NOT_A_PORT,
};

const uint16_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
	(uint16_t) &PORTE,
	(uint16_t) &PORTF,
	(uint16_t) &PORTG,
	NOT_A_PORT,
};

const uint16_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PIN,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
	(uint16_t) &PINE,
	(uint16_t) &PINF,
	(uint16_t) &PING,
	NOT_A_PIN,
};

// maybe pins ports
const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PE,PE,PE,PE,PE,PE,PE,PE, 
	PB,PB,PB,PB,PB,PB,PB,PB, 
	PC,PC,PC,PC,PC,PC,PC,PC, 
	PD,PD,PD,PD,PD,PD,PD,PD, 
	PA,PA,PA,PA,PA,PA,PA,PA, 
	PF,PF,PF,PF,PF,PF,PF,PF,  
	PG,PG,PG,PG,PG,          
};

// maybe pins ports ids
const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	_BV(5),	_BV(6),	_BV(7), // 0o
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	_BV(5),	_BV(6),	_BV(7), 
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	_BV(5),	_BV(6),	_BV(7), 
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	_BV(5),	_BV(6),	_BV(7), 
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	_BV(5),	_BV(6),	_BV(7), 
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	_BV(5),	_BV(6),	_BV(7), 
	_BV(0), _BV(1), _BV(2),	_BV(3),	_BV(4),	                        
};

// maybe pins ports timer (pwm)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
	NOT_ON_TIMER, NOT_ON_TIMER,	NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, // E
	NOT_ON_TIMER, NOT_ON_TIMER,	NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, // B
	NOT_ON_TIMER, NOT_ON_TIMER,	NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, // C
	NOT_ON_TIMER, NOT_ON_TIMER,	NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, // D 
	TIMER0A     , TIMER0B     ,	TIMER1A     , TIMER1B     , TIMER2A     , TIMER2B     , TIMER3A     , TIMER3B     , // A 
	NOT_ON_TIMER, NOT_ON_TIMER,	NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, // F 
	NOT_ON_TIMER, NOT_ON_TIMER,	NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,                                           // G
};

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial
#define SERIAL_PORT_HARDWARE1       Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1
#endif
