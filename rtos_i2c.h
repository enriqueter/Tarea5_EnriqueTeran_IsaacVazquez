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
	uint32_t  baudrate;				/**I2C Baud rate*/
	rtos_i2c_number_t i2c_number;	/**I2C to use*/
	rtos_i2c_port_t port;			/**Kinietis Port*/
	uint8_t SCL_pin;				/**Pin of Serial Clock*/
	uint8_t SDA_pin;				/**Pin of Serial Data*/
	uint8_t pin_mux;				/**Pin Configuration*/
}rtos_i2c_config_t;

rtos_i2c_flag_t rtos_i2c_init(rtos_i2c_config_t config);
rtos_i2c_flag_t rtos_i2c_transfer(rtos_i2c_number_t i2c_number, uint8_t * buffer, uint16_t length, uint16_t slave_addr, uint16_t subaddr, uint8_t subsize);
rtos_i2c_flag_t rtos_i2c_receive(rtos_i2c_number_t i2c_number, uint8_t * buffer, uint16_t length, uint16_t slave_addr, uint16_t subaddr, uint8_t subsize);

#endif /* RTOS_I2C_H_ */
