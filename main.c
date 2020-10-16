/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    tarea6.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "BMI160.h"
#include "rtos_i2c.h"
#include "fsl_uart.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
void i2c_init_task(void * args);
void IMU_dataget_task(void * args);
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    /* Init FSL debug console. */
    BOARD_InitDebugConsole();


    PRINTF("Hello World\n");



    xTaskCreate(i2c_init_task, "i2c_init_task", 110, NULL, 1, NULL);
    xTaskCreate(IMU_dataget_task, "IMU_dataget_task", 110, NULL, 1, NULL);
    BMI160_Initalization();
    vTaskStartScheduler();
    /* Force the counter to be placed into memory. */

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    }
    return 0 ;
}

void i2c_init_task(void * args){

	rtos_i2c_config_t config;
	config.baudrate = 100000;
	config.i2c_number = rtos_i2c_1;
	config.port = rtos_i2c_portC;
	rtos_i2c_init(config);
	BMI160_Initalization();
	vTaskSuspend(100000000000000000000);
}

void IMU_dataget_task(void *args){
	Accel_data_t accel_data_out;
	Gyro_data_t gryo_data_out;


	gryo_data_out = BMI160_GRYO_Read();
	accel_data_out = BMI160_ACCEL_Read();

	PRINTF("Accelerometer values x:%d y:%d z:%d \n", accel_data_out.x, accel_data_out.y, accel_data_out.z);
	PRINTF("Accelerometer values x:%d y:%d z:%d \n", gryo_data_out.x, gryo_data_out.y, gryo_data_out.z);

}
