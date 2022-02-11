//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
		printf("\n\nTeszt\n\n");
    volatile uint32_t ui32Loop;


	  // ADC part-----------
			uint32_t ui32Value;
		//
		// Enable the ADC0 module.
		//
		SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
		//
		// Wait for the ADC0 module to be ready.
		//
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
		{ }
		//
		// Enable the first sample sequencer to capture the value of channel 0 when
		// the processor trigger occurs.
		//
		ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 0,
		ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
		ADCSequenceEnable(ADC0_BASE, 0);
		/*
		while(1)
    {
			//
			// Trigger the sample sequence.
			//
			ADCProcessorTrigger(ADC0_BASE, 0);
			//
			// Wait until the sample sequence has completed.
			//
			while(!ADCIntStatus(ADC0_BASE, 0, false))
			{ }
			//
			// Read the value from the ADC.
			//
			ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value);
			 //
        // Delay for a bit.
        //
        for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {
        }
		}
		*/
		// ADC part----------- end
		
		
		// GPIO part-----------
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutputOD(GPIO_PORTF_BASE, GPIO_PIN_3);
		GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_STRENGTH_8MA,  GPIO_PIN_TYPE_OD);
    //
    // Loop forever.
    //
		
    while(1)
    {
			//
			// Trigger the sample sequence.
			//
			ADCProcessorTrigger(ADC0_BASE, 0);
			//
			// Wait until the sample sequence has completed.
			//
			while(!ADCIntStatus(ADC0_BASE, 0, false))
			{ }
			//
			// Read the value from the ADC.
			//
			ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value);


				if(ui32Value > 0xAF0){ //Motor on
       
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
					
				}
				
				else{ //Motor off
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
				}
        //
        // Delay for a bit.
        //
        for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {
        }
    }
		
		// GPIO part-----------end
}
