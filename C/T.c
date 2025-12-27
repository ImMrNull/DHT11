#include <mega16.h>
#include <stdio.h>
#include <delay.h>
#include <DHT11.h>
void main(void)
{
int a,b;
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;
DHT_init();
while (1)
      {
      DHT_read(&a,&b); 
      printf("T:%d\n",a);    
      printf("_____\n");
      printf("H:%d\n",b);
      delay_ms(1000);
      }
}
