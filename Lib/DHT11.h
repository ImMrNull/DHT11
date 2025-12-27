#ifndef _DELAY_INCLUDED_
#include <delay.h>
#endif 

#ifdef _MODEL_TINY_
#Error "i can't sapport ic ATtiny"
#endif

#ifndef _IO_INCLUDED_
#include <io.h>
#endif    

#pragma warn+
/////////////////////////////////////
void DHT_init(void);
int DHT_read(int *temp,int *humidity);
///////////////////////////////////
void DHT_init(void)
{
#pragma warn+
#define    _ddr        DDRA         //
#define    _port       PORTA      //      port name 
#define    _pin         PINA        //
#define    _ddr_        DDRA0      //
#define    _port_       PORTA0   //    port number
#define    _pin_         PINA0     //
#pragma warn-      
}
int DHT_read(int *temp,int *humidity)
{
unsigned char bytes[5];
unsigned char sum;
unsigned int bitcount=8;
unsigned int loopcount=0;
unsigned int byteid=0;
int i=0;
              for (i=0; i< 5; i++) bytes[i] = 0;

        _ddr|=(1<<_port_);  
        _port&=~(1<<_port_);    
        delay_ms(20);
        _port|=(1<<_port_);
        delay_us(2);
        _ddr&=~(1<<_port_); 
        _port&=~(1<<_port_);
     loopcount=0;    
        for (i=0; i< 5; i++) bytes[i] = 0;

        loopcount=0;    
        while(!(_pin&(1<<_pin_)))
        { 
        delay_us(40);
        loopcount++;  
        }      
                 if (loopcount>80) return -2;
        loopcount=0;    
        while((_pin&(1<<_pin_)))
        { 
        delay_us(1);
        loopcount++;
        }     
                 if (loopcount>80) return-2;
        for(i=0;i<40;i++){ 
        loopcount=0;    
                while(!(_pin&(1<<_pin_))){}  
                while((_pin&(1<<_pin_)) && loopcount<100){loopcount++;delay_us(1);}
                if(loopcount>15)
        bytes[byteid] |= (1 << bitcount);
                if (bitcount == 0)  
                {
                bitcount = 7;    
                byteid++;      
                }
                else bitcount--; 
        } 
        *humidity    = bytes[0];
        *temp = bytes[2];
        sum = (bytes[0] + bytes[1]+ bytes[2]+ bytes[3])&0xff;  
               if (bytes[4] != sum) return -1;  
        *humidity  /= 2; 
        *temp /= 2;
        return 0;
        }


#pragma warn- 