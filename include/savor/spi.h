#ifndef SPI_H

#define SPI_H

#include<avr/io.h>

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#   define DDR_SPI DDRB
#   define DD_MOSI PORTB3
#   define DD_MISO PORTB4
#   define DD_SCK  PORTB5
#   define DD_SS   PORTB2
#else
#	warning "Device not currently supported"
#endif

typedef enum {
	FREQ_4,
	FREQ_16,
	FREQ_64,
	FREQ_128,
	FREQ_2,
	FREQ_8,
	FREQ_32
} SPI_FREQ_T;

void SPI_MasterInit(void);

// Transmit and receive simultaniously
uint8_t SPI_Tranceive(uint8_t data);

#define SPI_Receive() SPI_Tranceive(0xFF)

void SPI_SetFreq(SPI_FREQ_T freq);


#endif
