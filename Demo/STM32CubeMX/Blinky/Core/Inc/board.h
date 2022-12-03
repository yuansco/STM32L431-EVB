
#ifndef __BOARD_H__
#define __BOARD_H__


#include <stdint.h>
#include <stdio.h>

/**
 * Firmware version and auto build date
 * 
 * BUILD_DATE will update by build.sh, Don't modify date directly.
 */
#define VERSION "V1.0"
#define BUILD_DATE "2022.10.24"


#define UART_DEBUG
//#undef UART_DEBUG

#ifdef UART_DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(args...)
#endif


/**
 *  I2C Scan
 * 
 *  Support I2C Scan function.
 */
#define I2C_SCAN
//#undef I2C_SCAN


/**
 * Board loop delay
 * main function loop delay as well as oled update delay.
 */
#define CONFIG_BOARD_LOOP_TIME_MS 300

/* util */

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

#define BIT(nr) (1U << (nr))

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define ABS(x) ((x) >= 0 ? (x) : -(x))



/* main function API */
void BOARD_Init();
void BOARD_Loop();



#endif /* __BOARD_H__ */


