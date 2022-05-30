
/**
  TMR1 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr1.c

  @Summary
    This is the generated source file for the TMR1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR1. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ64GA002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
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

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "mcc.h"
#include "tmr1.h"

/**
 Section: File specific functions
*/
void (*TMR1_InterruptHandler)(void) = NULL;
void TMR1_CallBack(void);

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    volatile bool           timerElapsed;
    /*Software Counter value*/
    volatile uint8_t        count;

} TMR_OBJ;

static TMR_OBJ tmr1_obj;

/**
  Section: Driver Interface
*/

void TMR1_Initialize (void)
{
    //TMR1 0; 
    TMR1 = 0x00;
    //Period = 0.00003 s; Frequency = 70000000 Hz; PR1 2099; 
    PR1 = 0x833;
    //TCKPS 1:1; TON enabled; TSIDL disabled; TCS FOSC/2; TSYNC disabled; TGATE disabled; 
    T1CON = 0x8000;

    if(TMR1_InterruptHandler == NULL)
    {
        TMR1_SetInterruptHandler(&TMR1_CallBack);
    }

    IFS0bits.T1IF = false;
    IEC0bits.T1IE = true;
	
    tmr1_obj.timerElapsed = false;

}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _T1Interrupt (  )
{
    extern float kp_v;
    extern float ki_v;
    extern float kd_v;

    
    extern float kp_i;
    extern float ki_i;
    extern float kd_i;
    
    
    extern float Vref;
    extern float Iref;
    extern float Iactual;
    extern float Vactual;
    extern float Vactual_AC;
    extern float cntrl;
    extern float cntrl_max;
    extern float cntrl_min;
    
    extern int vloop_cnt;
    extern float Iac;
    
    extern float sum_Vref;
    extern float cnt_Vref;
    
    extern float e[3];
    extern float m[3];
    
    /* Check if the Timer Interrupt/Status is set */
//    PORTBbits.RB1 = 1;
    //***User Area Begin
    //Sensor stuff
//    Vactual = ((float)ADC1BUF0/1023.0)*5.0;
//    Vactual = (Vactual*((12000+100)/100))/10;
//    Vactual = (float)ADC1BUF0 * 0.06353861192;
    Vactual = (float)ADC1BUF0 * 0.05913978495;
//    Iactual = ((float)ADC1BUF1/1023.0)*5.0;
//    Iactual = (2.5 - Iactual)/0.1;
    Iactual = (25 - 0.04887585532*(float)ADC1BUF1)*1.0;
    Vactual_AC = (float)ADC1BUF2 * 0.05913978495;
    //Sensor stuff ends
    
//    printf("%.1f \r", Iactual);
    
//    error_v = Vref - Vactual;
//    diff_error_v = error_v - prev_error_v;
//    summ_error_v += error_v;
//    prev_error_v = error_v;
//    
//    cntrl = kp_v*error_v + kd_v*diff_error_v + ki_v*summ_error_v;

//    Iref = Iac*Vactual_AC;
    Iref = Vactual_AC*0.20;
    
//    m[0] = m[1];
//    e[0] = e[1];
//    e[1] = e[2];
//    e[2] = Iref - Iactual;
//    
//    m[1] = (kp_i + ki_i + kd_i)*e[2] - (kp_i + 2*kd_i)*e[1] + kd_i*e[0] + m[0];
    
    
    
    
    m[0] = m[1];
    e[2] = e[1];
    e[1] = e[0];
    
    e[0] = Iref - Iactual;
    
    m[1] = (kp_i + ki_i + kd_i)*e[0] - (kp_i + 2*kd_i)*e[1] + kd_i*e[2] + m[0];
    
//    if(cntrl >= 690.0){
//        cntrl = 690.0;
//    }
//    else if(cntrl <= 0.0){
//        cntrl = 0.0;
//    }
//    else{
//        cntrl = cntrl;
//    }
    
    
    
    if(m[1] >= cntrl_max){
        m[1] = cntrl_max;
    }
    else if(m[1] <= cntrl_min){
        m[1] = cntrl_min;
    }
    else{
        m[1] = m[1];
    }
    
    
    

        OC1RS = (int)m[1];
        
        
        sum_Vref += Vactual;
        cnt_Vref += 1.0;
    
    vloop_cnt++;
    vloop_cnt = 0;
    if(vloop_cnt == 20){
        Vactual = sum_Vref/cnt_Vref;
        cnt_Vref = 0.0;
        sum_Vref = 0.0;
        vloop_cnt = 0;      
        
        if(Vactual < Vref){
            Iac = Iac + 0.001;
        }
        else if(Vactual > Vref){
            Iac = Iac - 0.001;
        }
        else{
            Iac = Iac;
        }
        
        
        if(Iac >= 1.25){
            Iac = 1.25;
        }
        else if(Iac <= 0.0){
            Iac = 0.0;
        }
        else{
            Iac = Iac;
        }
//        Iac = 0.25;
//        printf("%.1f %.1f \r", Vactual, Iac);
    }
    
//    PORTBbits.RB1 = 0;
    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    if(TMR1_InterruptHandler) 
    { 
           TMR1_InterruptHandler(); 
    }

    //***User Area End

    tmr1_obj.count++;
    tmr1_obj.timerElapsed = true;
    IFS0bits.T1IF = false;
}

void TMR1_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Period16BitGet( void )
{
    return( PR1 );
}

void TMR1_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Counter16BitGet( void )
{
    return( TMR1 );
}


void __attribute__ ((weak)) TMR1_CallBack(void)
{
    // Add your custom callback code here
}

void  TMR1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.T1IE = false;
    TMR1_InterruptHandler = InterruptHandler; 
    IEC0bits.T1IE = true;
}

void TMR1_Start( void )
{
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;

    /*Enable the interrupt*/
    IEC0bits.T1IE = true;

    /* Start the Timer */
    T1CONbits.TON = 1;
}

void TMR1_Stop( void )
{
    /* Stop the Timer */
    T1CONbits.TON = false;

    /*Disable the interrupt*/
    IEC0bits.T1IE = false;
}

bool TMR1_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr1_obj.timerElapsed;

    if(status == true)
    {
        tmr1_obj.timerElapsed = false;
    }
    return status;
}

int TMR1_SoftwareCounterGet(void)
{
    return tmr1_obj.count;
}

void TMR1_SoftwareCounterClear(void)
{
    tmr1_obj.count = 0; 
}

/**
 End of File
*/
