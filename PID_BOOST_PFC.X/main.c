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
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ64GA002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
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

/*
                         Main application
 */
float kp_v = 2.1;
float ki_v = 0.774;
float kd_v = 0.00;

//float kp_i = 24.9956;
//float ki_i = 4.55;
//float kd_i = 0.4;

//float kp_i = 3.29956;
//float ki_i = 0.16;  //1.55 for maximum of 0.35

float kp_i = 12.0059956;        //400Vdc
float ki_i = 8.10;  //1.55 for maximum of 0.35

//float kp_i = 12.0059956;
//float ki_i = 10.10;  //1.55 for maximum of 0.35

//float kp_i = 12.29956;
//float ki_i = 1.4;  //1.55 for maximum of 0.35
//as one goes higher in the output Vref voltage; the ki_i value must decrease. 
//The gain value stays. I am yet to observe an adverse change in the high kp_i value.
//I find something remarkable. The severe reduction in the ki_i values
//produces the most incredible results. A beautiful sinusoidal waveform.
//Cheers!!!
//Thus, it seems as though the secret was always a super fast loop.
float kd_i = 0.4;

float Vref = 40.0;
float Iref = 2.0;
float Iactual = 0.0;
float Vactual = 0.0;
float Vactual_AC = 0.0;
float cntrl = 0.0;
float cntrl_max = 690.0;
float cntrl_min = 0.0;

int vloop_cnt = 0;
float Iac = 0.0;

float sum_Vref = 0.0;
float cnt_Vref = 0.0;

float e[3] = {0.0};
float m[3] = {0.0};

//extern int i = 0;

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        // Add your application code
//        OC1RS = 70;
    }

    return 1;
}
/**
 End of File
*/

