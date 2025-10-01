#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000
#include <xc.h>

#define chave_mais !PORTAbits.RA2
#define chave_menos !PORTAbits.RA1

int display[10] = {0xee, 0x28, 0xcd, 0x6d, 0x2b, 0x67, 0xe7, 0x2c, 0xef, 0x6f};

void atualizaDisplay(int numero)
{
    int dezena = numero / 10;
    int unidade = numero - (dezena * 10);
    PORTB = display[dezena];
    __delay_ms(10);
    PORTB = display[unidade];
    PORTBbits.RB4 = 1;
    __delay_ms(10);
}

void main(void)
{
    TRISA = 0xFF;
    TRISB = 0x00;
    PORTB = 0x00;
    uint8_t numero = 0;

    for (;;)
    {
        if (chave_mais)
        {
            numero++;
            if (numero > 99)
                numero = 0;
            while(!PORTAbits.RA2)
            {
                atualizaDisplay(numero);
            }
        }
        
        if (chave_menos)
        {
            numero--;
            if (numero > 99)
            {
                numero = 99;
            }
            while(!PORTAbits.RA1)
            {
                atualizaDisplay(numero);
            }
        }
        
        
        
        atualizaDisplay(numero);
    }

}
