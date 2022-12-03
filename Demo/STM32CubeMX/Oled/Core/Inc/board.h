
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
#define BUILD_DATE "2022.12.03"


#define UART_DEBUG
//#undef UART_DEBUG

#ifdef UART_DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(args...)
#endif

/**
 * LED Behavior
 * 
 * Slowly blinking LED in Normal mode,
 * Fastly blinking LED before reset mcu if any error happened.
 * 
 * Normal: LED 1 second on, 1 second off
 * Error: LED 0.1 second on, 0.1 second off
 */
#define  CONFIG_LED_NORMAL
#define  CONFIG_LED_NORMAL_PIN LED_BLUE_Pin
#define  CONFIG_LED_NORMAL_PORT LED_BLUE_GPIO_Port
#define  CONFIG_LED_NORMAL_BLINK_MS 1000
//#undef CONFIG_LED_NORMAL

#define  CONFIG_LED_ERROR
#define  CONFIG_LED_ERROR_PIN LED_RED_Pin
#define  CONFIG_LED_ERROR_PORT LED_RED_GPIO_Port
#define  CONFIG_LED_ERROR_SEC 3
#define  CONFIG_LED_ERROR_TIME_MS (CONFIG_LED_ERROR_SEC * 1000)
#define  CONFIG_LED_ERROR_BLINK_MS 100
//#undef CONFIG_LED_ERROR


/**
 *  I2C Scan
 * 
 *  Support I2C Scan function.
 */
#define I2C_SCAN
//#undef I2C_SCAN



/**
 * OLED SSD1306
 */

#define SSD1306_OLED
//#undef SSD1306_OLED

#define SSD1306_USE_I2C

// I2C Configuration
#define SSD1306_I2C_PORT        hi2c1
#define SSD1306_I2C_ADDR        (0x3C << 1)

// Mirror the screen if needed
// #define SSD1306_MIRROR_VERT
// #define SSD1306_MIRROR_HORIZ

// Set inverse color if needed
// # define SSD1306_INVERSE_COLOR

// Include only needed fonts
//#define SSD1306_INCLUDE_FONT_6x8
//#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
//#define SSD1306_INCLUDE_FONT_16x26

// Some OLEDs don't display anything in first two columns.
// In this case change the following macro to 130.
// The default value is 128.
// #define SSD1306_WIDTH           130

// The height can be changed as well if necessary.
// It can be 32, 64 or 128. The default value is 64.
// #define SSD1306_HEIGHT          32



/**
 * Task 1 function
 */
#define CONFIG_TASK1
#define CONFIG_TASK1_TIME_MS 1000


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


