#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t contador_ms = 0;
volatile uint16_t limite_ms = 500;

ISR(TIMER1_COMPA_vect){
    contador_ms++;
    if(contador_ms >= limite_ms){
        PORTD ^= (1<<PD1);
        contador_ms = 0; 
    }
}

int main(){
    DDRD |= (1 << DDD1);
    DDRD &= ~((1 << DDD2) | (1 << DDD3));
    PORTD |= (1 << PD2) | (1 << PD3);
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 249;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    sei();
    while(1){
        uint8_t estado_dip = (~PIND >> 2) & 0x03;
        switch(estado_dip){
            case 0b00:
                limite_ms = 500;
                break;
            case 0b01:
                limite_ms = 250;
                break;
            case 0b10:
                limite_ms = 100;
                break;
            default:
                limite_ms = 100;
                break;
        }
    }
}
