/*
 * rtos_i2c.c
 *
 *  Created on: 15 oct. 2020
 *      Author: etera
 */


#include "rtos_i2c.h"

/* DRIVERS include */
#include "fsl_i2c.h"
#include "fsl_clock.h"
#include "fsl_port.h"

/* RTOS include */
#include "FreeRTOS.h"
#include "semphr.h"


/**Defines number of serial ports*/
#define NUMBER_OF_SERIAL_PORTS (3)

/* INLINE Functions Definitions */
static inline void rtos_i2c_clockenable(rtos_i2c_number_t i2c_number);
/**Enables Port Clock*/
static inline void rtos_i2c_portclock_enable(rtos_i2c_port_t);
/**Gets the I2C to use*/
static inline I2C_Type * get_i2c_base(rtos_i2c_number_t);
/**Gets Port to use I2C*/
static inline PORT_Type * get_port_base(rtos_i2c_port_t);
/**Callback function when I2C is finished*/
static void fsl_i2c_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData);

typedef struct
{
	uint8_t is_init;								/**Flag to detect I2C initialization*/
	i2c_master_handle_t fsl_i2c_master_handle;		/**I2C callback handle*/
	SemaphoreHandle_t mutex_tx_rx;					/**Mutex to protect access through I2C*/
	SemaphoreHandle_t tx_rx_sem;					/**Binary to signal status of actions through I2C*/
}rtos_i2c_hanlde_t;
