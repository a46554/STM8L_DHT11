
//adapted from http://www.amobbs.com/thread-5517880-1-1.html?_dsign=d9eb7efa//

#include "stm8l15x.h"
#include "DHT11_LIB.h"
#include "BSP.h"

unsigned char U8FLAG,U8temp;
unsigned char date[5] = {0};
extern void Delayms(unsigned int us);
extern void Delay10Us(unsigned int us);


void GetDHT11_Data(unsigned char *tmp)
{

    unsigned char i,j;

    DHT11_OUT();
    DHT11_Low();      //DHT11=0
    Delayms(18); 	  //delay 18ms
    DHT11_High();     //DHT11=1
    Delay10Us(2);	  //delay 20us
    DHT11_IN();       //DHT11_input

    if(DHT11_Read())
        U8FLAG=1;
    while(!(DHT11_Read())) {
        U8FLAG=2;

        while((!(DHT11_Read()))&&U8FLAG++); //wait DHT11 fist 80us low singal

        if(U8FLAG==1)
            break;
        U8FLAG=2;

        while((DHT11_Read())&&U8FLAG++); //wait DHT11 fist 80us high singal

        if(U8FLAG==1)
            break;

        for(j = 0; j<5; j++) { //read 5 bytes data
            for(i=0; i<8; i++) {
                U8FLAG=2;
                while((!(DHT11_Read()))&&U8FLAG++);//wait the first 50us low singal
                if(U8FLAG==1)
                    break;

                Delay10Us(3);
                U8temp=0;

                if(DHT11_Read())
                    U8temp=1;//wait the high singal if over 30us the this bit set to 1

                U8FLAG=2;
                while((DHT11_Read())&&U8FLAG++);

                if(U8FLAG==1)
                    break;

                date[j]<<=1;
                date[j]|=U8temp;
            }

        }

        if((date[0]+date[2]) != date[4]) { // check data with check sum
            date[0] = date[2] = date[4] = 0;
        }

        tmp[0] = (unsigned int)date[0] % 10;
        tmp[1] = (unsigned int)date[0] % 100 / 10;
        tmp[2] = (unsigned int)date[2] % 10;
        tmp[3] = (unsigned int)date[2] % 100 / 10;


        DHT11_OUT();
        DHT11_High();
    }

}