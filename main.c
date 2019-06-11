#include<18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG
#use delay(clock=40000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#use fast_io(b)

#int_timer0
int16 countMS;
int countLed;
void isr_timer0()
{
    countMS++;
    countLed++;
    set_timer0(100);
}

#int_RDA
char letra;
void isr_serial()
{
    if(kbhit(1))
    {
        letra = getch();
    }
}


void main()
{
    //setup_oscillator(OSC_40MHZ);
    setup_adc_ports(NO_ANALOGS);
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64|RTCC_8_BIT);
    enable_interrupts(INT_TIMER0);
    enable_interrupts(INT_RDA);
    enable_interrupts(GLOBAL);
    set_tris_b(0x00);
    int16 muestraMS = 0;
    int estadoLed = 0;
    while(TRUE)
    {
    printf("Bienvenido, que desea hacer? [R] Poner en 0 [S] Inicia la cuenta [A] Parar y mostrar");
    switch(letra)
    {
        case 'R':
            countMS = 0;
            muestraMS = 0;
            break;
        case 'S':
            countMs = muestraMs;
            break;
        case 'A':
            muestraMS = countMS;
            printf("La cuenta es: %lu\n", muestraMS);
            break;
        default:
            printf("Letra incorrecta");
            break;
    }
    if(countLed == 100)   
    {
       if (estadoLed == 0)
       {
          estadoLed = 1;
          output_high(PIN_B0);
          countLed = 0;
       }
       else
       {
          estadoLed = 0;
          output_low(PIN_B0);
          countLed = 0;
       }
    }
    }
}
