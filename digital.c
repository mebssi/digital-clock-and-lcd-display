#include <REGX51.H>

/* Seven-segment pins: P2.0-P2.7
   Order: a, b, c, d, e, f, g, dp
   Common Anode: segment ON = 0
*/

/* Digit select pins: P1.0-P1.3
   Assumption: digit ON = 1
*/

unsigned char code segCA[10] = {
    0xC0,  // 0
    0xF9,  // 1
    0xA4,  // 2
    0xB0,  // 3
    0x99,  // 4
    0x92,  // 5
    0x82,  // 6
    0xF8,  // 7
    0x80,  // 8
    0x90   // 9
};

unsigned char hour = 12;
unsigned char minute = 0;
unsigned char second = 0;

unsigned int ms_count = 0;
unsigned char scan = 0;

unsigned char display[4];

/* Update the four display digits */
void update_display(void)
{
    display[0] = hour / 10;
    display[1] = hour % 10;
    display[2] = minute / 10;
    display[3] = minute % 10;
}

/* Timer 0 interrupt: approximately every 1 ms
   Assumes an 11.0592 MHz crystal.
*/
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;

    /* Turn off all digits before changing segments */
    P1 = 0x00;

    /* Output the selected number */
    P2 = segCA[display[scan]];

    /* Enable one digit at a time */
    P1 = (1 << scan);

    scan++;
    if (scan >= 4)
        scan = 0;

    ms_count++;

    if (ms_count >= 1000)
    {
        ms_count = 0;

        second++;

        if (second >= 60)
        {
            second = 0;
            minute++;
        }

        if (minute >= 60)
        {
            minute = 0;
            hour++;
        }

        if (hour >= 24)
        {
            hour = 0;
        }

        update_display();
    }
}

void main(void)
{
    /* Initialize display */
    P1 = 0x00;
    P2 = 0xFF;

    update_display();

    /* Configure Timer 0, Mode 1 (16-bit timer) */
    TMOD = (TMOD & 0xF0) | 0x01;

    TH0 = 0xFC;
    TL0 = 0x66;

    /* Enable Timer 0 interrupt */
    ET0 = 1;
    EA = 1;

    /* Start Timer 0 */
    TR0 = 1;

    while (1)
    {
        /* Display and clock updated by Timer 0 ISR */
    }
}
