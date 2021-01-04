/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  PIC32MM0256GPM048
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.35
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"

// for kx224
/*
#define XOUT_L 0x06
#define WHO_AM_I 0x0F
#define CNTL1 0x18
#define CNTL2 0x19
#define ODCNTL 0x1B
#define COTR 0x0C
*/

// for kx134
#define XOUT_L 0x08
#define WHO_AM_I 0x13
#define CNTL1 0x1B
#define CNTL2 0x1C
#define ODCNTL 0x21
#define COTR 0x12

uint8_t writeByte( unsigned char adr, unsigned char w_data);
uint8_t readByte( unsigned char adr);
void kx224_POR();
void kx224_init();


extern uint8_t buf24mem[12000];  // 2000 samples room
extern uint8_t buf24memRD[12000];

extern uint8_t flag;

#if 0
uint8_t myWriteBuffer1[6000]; 
uint8_t myReadBuffer1[6000];
#endif

#if 0 //2020.05.08
uint8_t myWriteBuffer1[12000]; 
uint8_t myReadBuffer1[12000];
#endif

#if 1
uint8_t myWriteBuffer1[60]; 
uint8_t myReadBuffer1[60];
#endif

uint8_t writeByte( unsigned char adr, unsigned char w_data) {

    
	uint8_t myWriteBuffer[] = {adr,w_data}; 
	uint8_t myReadBuffer[]={0x0,0x0};

 	//uint8_t tar_adr;
 	//tar_adr = adr | 0x80;
 	
        //uint8_t data[]={tar_adr,w_data};   // MSB is high
	//uint8_t rawtemp[]={0x0,0x0};

	SPI1_Exchange8bitBuffer(myWriteBuffer, sizeof(myWriteBuffer), myReadBuffer);
	
	return 0;
}

uint8_t readByte( unsigned char adr) {

    
	uint8_t myWriteBuffer[] = {(adr | 0x80),0x00}; 
	uint8_t myReadBuffer[]={0x0,0x0};

 	//uint8_t tar_adr;
 	//tar_adr = adr | 0x80;
 	
        //uint8_t data[]={tar_adr,w_data};   // MSB is high
	//uint8_t rawtemp[]={0x0,0x0};

	SPI1_Exchange8bitBuffer(myWriteBuffer, sizeof(myWriteBuffer), myReadBuffer);
	
	return myReadBuffer[1];
}

void kx224_POR(){
    uint8_t a;
    a=readByte(WHO_AM_I);
    writeByte(0x7f,0x00);
    writeByte(CNTL2,0x00);
    writeByte(CNTL2,0x80);
    while (flag==0)
        ;
    a=readByte(WHO_AM_I);
    flag=0;

    while (flag==0)
        ;
    a=readByte(WHO_AM_I);
    flag=0;
    
    while(readByte(COTR) != 0x55)
        a=readByte(WHO_AM_I);
        a=readByte(WHO_AM_I);
}
    
 #define SYS_CLK_FREQ 8000000
 
void delay_m(unsigned int msec){
    //volatile unsigned int start = _CP0_GET_COUNT();
    unsigned int start = _CP0_GET_COUNT();
    while( _CP0_GET_COUNT() - start < ( msec * SYS_CLK_FREQ / 2 / 1000 ) )
        Nop();
    return;
}

 

void kx224_init(){
    
     uint8_t a;
    //a=readByte(WHO_AM_I);
    /*
    writeByte(0x7f,0x00);
    
    writeByte(CNTL2,0x00);
    writeByte(CNTL2,0x80);
    a=readByte(CNTL2);
    a=readByte(CNTL2);
    delay_m(8000);
    a=readByte(CNTL2);
    a=readByte(CNTL2);
    
    a=readByte(WHO_AM_I);
    a=readByte(WHO_AM_I);

    writeByte(ODCNTL,0x0F);  // ODR=25600Hz
    delay_m(80);
    a=readByte(ODCNTL);
    a=readByte(WHO_AM_I);
    a=readByte(ODCNTL);
    a=readByte(COTR);   // COTR=0x55
    writeByte(CNTL2,0x7F);  // to change COTR value
    a=readByte(COTR);   // maybe COTR=0xAA
    writeByte(CNTL2,0x3F);  // return to original
    */
    writeByte(CNTL1,0x00);
	writeByte(ODCNTL,0x0F);  // ODR=25600Hz
    writeByte(CNTL1,0xD0);   // 32g
    delay_m(80);
    //delay_m(800);
    /*
    a=readByte(CNTL1); 
    a=readByte(CNTL1);
	*/
    
}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    //kx224_POR();

    kx224_init();
    
    LATCbits.LATC7 = 1;
    int i;

#if 0
    for(i=0;i<6000;i++)
        //myWriteBuffer1[i]=i % 256;
        myWriteBuffer1[i]=48 + (i % 6);
#endif 

#if 0 // 2020.05.08
    for(i=0;i<12000;i++)
        //myWriteBuffer1[i]=i % 256;
        //myWriteBuffer1[i]=48 + (i % 10);
        myWriteBuffer1[i]=48 + (i % 6);
#endif  

#if 0  // 2020.05.20
    //for(i=0;i<80;i++)
    for(i=0;i<60;i++)
        myWriteBuffer1[i]=48 + (i % 6);
        //myWriteBuffer1[i]=0x01;
#endif 
    while (1)
    {
        // Add your application code
#if 1

        //if (flag==1){
        
        if ((PORTBbits.RB10==1) && (flag==1)){
            //LATCbits.LATC7 ^= 1;
            LATCbits.LATC7 = 0;
            flag=0;
            //transfer process
#if 1  // 2020.05.20
            SPI3_Exchange8bitBuffer(buf24mem, sizeof(buf24mem), buf24memRD);
#endif
            
#if 0   // 2020.05.20
            SPI3_Exchange8bitBuffer(myWriteBuffer1, sizeof(myWriteBuffer1), myReadBuffer1); //2020.05.08
            //LATCbits.LATC7 ^= 1;
#endif
            LATCbits.LATC7 = 1;
        }

#endif
    }
    return 1; 
}
/**
 End of File
*/

