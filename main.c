#include<18LF4620.h>
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLPT1OSC                //Timer1 configured for higher power operation
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

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
    if(kbhit())
    {
        letra = getch();
    }
}

#use delay(clock=16000000)

void main()
{
    setup_oscillator(OSC_16MHZ);
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
