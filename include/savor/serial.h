#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <sys/types.h>

/* Use stdin so that printf can be used
 * Using fdev_setup_stream(stream, p, g, f)
 */

#define serial_ubrr(freq, baud) freq/16/baud-1

static FILE serial_stdout;

void serial_init();
int serial_putchar(char c, FILE *stream);

#endif
