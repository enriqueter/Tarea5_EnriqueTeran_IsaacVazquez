/*
 * rtos_i2c.h
 *
 *  Created on: 15 oct. 2020
 *      Author: etera
 */

#ifndef RTOS_I2C_H_
#define RTOS_I2C_H_

#include <stdint.h>

typedef enum {rtos_i2c_0, rtos_i2c_1, rtos_i2c_2} rtos_i2c_number_t;
typedef enum {rtos_i2c_portA,rtos_i2c_portB,rtos_i2c_portC,rtos_i2c_portD,rtos_i2c_portE} rtos_i2c_port_t;
typedef enum {rtos_i2c_sucess,rtos_i2c_fail} rtos_i2c_flag_t;

typedef struct
{
	uint32_t  i2c_baudrate;			/**Baud rate*/
	rtos_i2c_number_t i2c_number;	/**Number i2c */
	rtos_i2c_port_t i2c_port;		/**i2c k66 port*/
	uint8_t muxpin;					/**Mux_Config*/
	uint8_t Data_pin;				/**Serial Data pin*/
	uint8_t CLK_pin;				/**Serial Clock pin*/

}rtos_i2c_config_t;

rtos_i2c_flag_t rtos_i2c_init(rtos_i2c_config_t config);
rtos_i2c_flag_t rtos_i2c_transfer(rtos_i2c_number_t number, uint8_t * buffer, uint16_t length, uint16_t slave_addr, uint16_t subaddr, uint8_t subsize);
rtos_i2c_flag_t rtos_i2c_receive(rtos_i2c_number_t number, uint8_t * buffer, uint16_t length, uint16_t slave_addr, uint16_t subaddr, uint8_t subsize);

#endif /* RTOS_I2C_H_ */
