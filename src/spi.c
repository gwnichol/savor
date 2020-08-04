#include <savor/spi.h>
#include <avr/io.h>

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS);
	DDR_SPI &= ~(1<<DD_MISO);

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR);
	SPI_SetFreq(FREQ_16);
}

/* Send data over SPI and receive durring send
 */
uint8_t SPI_Tranceive(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;	
}

void SPI_SetFreq(SPI_FREQ_T freq)
{
	SPCR &= ~(0x3<<SPR0);
	SPCR |= (freq & 0x3)<<SPR0;

	SPSR &= ~(1<<SPI2X);
	SPSR |= ((freq>>2) & 0x1) << SPI2X;
}
