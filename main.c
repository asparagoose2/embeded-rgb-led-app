/*
 * File:   main.c
 * Author: duchovne
 *
 * Created on May 13, 2022, 10:22 AM
 */


#include "xc.h"
#include "RGB_LED.h"
#include "POT_ATD.h"
#include "BTNS.h"

#define THRESSHOLD_VALUE  25
#define OFF               0

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef enum
{
    CONFIG,
    DISPLAY,
} MODE;

typedef enum
{
    RED,
    GREEN,
    BLUE,       
} COLOR;

MODE current_mode = CONFIG;
COLOR current_color = RED;

int RED_VALUE = 1023;
int GREEN_VALUE = 1023;
int BLUE_VALUE = 1023;

void init() 
{
    LED_RGB_INIT();
    POT_ADC_INIT();
    BTNS_INIT();
}

int main(void) {
    init();
    int pot_val = 0;
     int pot_val2 = 0;
    while(1) {
        if(IS_PRESSED(S1))
        {
            while(IS_PRESSED(S1));
            current_mode = (current_mode == DISPLAY) ? CONFIG : DISPLAY;
        }
        if(IS_PRESSED(S2))
        {
            pot_val = READ_POT();
            pot_val2 = READ_POT();
            while(IS_PRESSED(S2));
            current_color = (++current_color) %3;
           
        }
        switch(current_mode)
        {
            case DISPLAY:
                SET_RGB_COLOR(RED_VALUE,GREEN_VALUE,BLUE_VALUE);
                break;
                
            case CONFIG:
                pot_val = READ_POT();
                switch(current_color)
                {
                    case RED:
                        RED_VALUE = ABS(pot_val2-pot_val) > THRESSHOLD_VALUE ? pot_val : RED_VALUE;
                        SET_RGB_COLOR(RED_VALUE,OFF,OFF);
                        break;
                    case GREEN:
                        GREEN_VALUE = ABS(pot_val2-pot_val) > THRESSHOLD_VALUE ? pot_val : GREEN_VALUE;
                        SET_RGB_COLOR(OFF,GREEN_VALUE,OFF);
                        break;
                    case BLUE:
                        BLUE_VALUE = ABS(pot_val2-pot_val) > THRESSHOLD_VALUE ? pot_val : BLUE_VALUE;
                        SET_RGB_COLOR(OFF,OFF,BLUE_VALUE);
                        break;
                }
                break;
                
        }
        
//        if(IS_PRESSED(S1) && !IS_PRESSED(S2))
//        {
//            SET_RGB_COLOR(1023,0,0);
//        } else if (!IS_PRESSED(S1) && IS_PRESSED(S2))
//        {
//            SET_RGB_COLOR(0,1023,0);
//        } else if (IS_PRESSED(S1) && IS_PRESSED(S2))
//        {
//            SET_RGB_COLOR(0,0,1023);
//        } else {
//            SET_RGB_COLOR(0,0,0);
//        }
    }
    return 0;
}
