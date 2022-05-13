/*
 * File:   RGB_LED.c
 * Author: ofir duchovne
 *
 * Created on May 13, 2022, 10:29 AM
 */


#include "xc.h"
#include "RGB_LED.h"

#define RED_LAT     LATAbits.LATA0
#define GREEN_LAT   LATAbits.LATA1
#define BLUE_LAT    LATCbits.LATC7

#define RED_TRIS    TRISAbits.TRISA0
#define GREEN_TRIS  TRISAbits.TRISA1
#define BLUE_TRIS   TRISCbits.TRISC7

#define RED_LED     OC1R
#define GREEN_LED   OC2R
#define BLUE_LED    OC3R


void LED_RGB_INIT() 
{
    RED_TRIS = 1 ;
    GREEN_TRIS = 1 ;
    BLUE_TRIS = 1 ;

    _RP26R = 13;
    _RP27R = 14;
    _RP23R = 15;

    OC1RS = 1023;                  
    OC1CON2bits.SYNCSEL = 0x1F;     //self-sync
    OC1CON2bits.OCTRIG = 0;         //sync mode
    OC1CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC1CON1bits.OCM = 0b110;        //edge aligned
    OC1CON2bits.TRIGSTAT = 1;       //manually trigger

    OC2RS = 1023;                  
    OC2CON2bits.SYNCSEL = 0x1F;     //self-sync
    OC2CON2bits.OCTRIG = 0;         //sync mode
    OC2CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC2CON1bits.OCM = 0b110;        //edge aligned
    OC2CON2bits.TRIGSTAT = 1;       //manually trigger

    OC3RS = 1023;                  
    OC3CON2bits.SYNCSEL = 0x1F;     //self-sync
    OC3CON2bits.OCTRIG = 0;         //sync mode
    OC3CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC3CON1bits.OCM = 0b110;        //edge aligned
    OC3CON2bits.TRIGSTAT = 1;       //manually trigger
}

void SET_RGB_COLOR(int red, int green, int blue) 
{
    RED_LED = red;
    GREEN_LED = green;
    BLUE_LED = blue;
}