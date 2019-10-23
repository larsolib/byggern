#include "stdint.h"

#include "../../lib/can/can_driver.h"
#include "../../lib/uart/uart.h"

#include "timer.h"

#define F_CPU 16000000

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

int main()
{
    timer_init();
    UART_init( MYUBRR );
    can_init(MODE_NORMAL);

    DDRA = (1<<PA3);
    DDRB = (1<<PB7);
    OCR0A = 90;
    can_message_t response;
    int counter = 1000;

    printf("%s\r\n", "Print");
    sei();
    while(1)
    {   

        if (!(can_message_read(&response))) // Returns 0 when successfully read
        {
            printf("id. %d", response.id);
            printf(" DATA: %d\n\r", response.data[0]);
        }

        while (counter) { counter--; }
        counter = 1000;
    }
    return 0;
}

