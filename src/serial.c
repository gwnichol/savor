#include <savor/serial.h>
#include <stdio.h>
#include <avr/io.h>

void serial_init(uint16_t ubrr){
    /*Set baud rate */
    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);    

    fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;
}

int serial_putchar(char c, FILE *stream){
    if (c == '\n') serial_putchar('\r', stream);

    while( !(UCSR0A & (1<<UDRE0)) );

    UDR0 = c;
    return 0;
}
