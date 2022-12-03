

#include "board.h"
#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************/
/* Extern Handle Type */

extern I2C_HandleTypeDef hi2c1;

#if defined(UART_DEBUG)
extern UART_HandleTypeDef huart1;
#endif




/******************************************************************************/
/* UART Debug  */

#if defined(__GNUC__) && defined(UART_DEBUG) && !defined(UART_DEBUG_GPIO)
int _write(int fd, char * ptr, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, HAL_MAX_DELAY);
  return len;
}
#elif defined (__ICCARM__) && defined(UART_DEBUG)
#include "LowLevelIOInterface.h"
size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  HAL_UART_Transmit(&huart1, (uint8_t *) buffer, size, HAL_MAX_DELAY);
  return size;
}
#elif defined (__CC_ARM) && defined(UART_DEBUG)
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif


/******************************************************************************/
/* I2C Scan function */

/**
 * scan 0x00 ~ 0x7f (0~127) 
 * retries: 2 times
 * timeout: 10 mS
 */

#ifdef I2C_SCAN

#define I2C_SCAN_TIMEOUT_MS 10
#define I2C_SCAN_RETRIES 2

void i2c_scan() {
  
  uint8_t i, re;

 	PRINTF("\r\nScanning I2C bus:\r\n");

 	for (i = 1; i < 128; i++) {

 	  re = HAL_I2C_IsDeviceReady(&hi2c1, (i << 1),
            I2C_SCAN_RETRIES, I2C_SCAN_TIMEOUT_MS);

 	  if (re == HAL_OK) {
      // received ACK
 		  PRINTF("\r\n0x%02X\r\n", i); 
      continue;
 	  }

    // No ACK received at that address
 		PRINTF(".");
 	}
 	PRINTF("\r\n");
}

#endif /* I2C_SCAN */

/******************************************************************************/
/* Task 1 */

void task_1(void) {

  PRINTF("Task 1 running!\r\n");
}

/******************************************************************************/
/* OLED SSD1306 */

#ifdef SSD1306_OLED

#define BUFF_SIZE 10

#define Y_OFFSET_LINE_0 0
#define Y_OFFSET_LINE_1 18
#define Y_OFFSET_LINE_2 36

static char line_1_str[BUFF_SIZE] = "Hi STM32  ";
static char line_2_str[BUFF_SIZE] = "          ";
static char line_3_str[BUFF_SIZE] = "          ";

void ssd1306_show(void) {

  ssd1306_Fill(Black);

  ssd1306_SetCursor(2, Y_OFFSET_LINE_0);
  ssd1306_WriteString(&line_1_str[0], Font_11x18, White);

  ssd1306_SetCursor(2, Y_OFFSET_LINE_1);
  ssd1306_WriteString(&line_2_str[0], Font_11x18, White);

  ssd1306_SetCursor(2, Y_OFFSET_LINE_2);
  ssd1306_WriteString(&line_3_str[0], Font_11x18, White);

  ssd1306_UpdateScreen();
}

#else
void ssd1306_show(void) {return;}
#endif


/******************************************************************************/
/* board init function */

void BOARD_Init() {
  PRINTF("Ver: %s-%s\r\n", VERSION, BUILD_DATE);

#ifdef FLASH_INIT
  FLASH_Init();
#endif

#ifdef SSD1306_OLED
  if (ssd1306_Init()) {
    PRINTF("ssd1306 init fail!\r\n");
    i2c_scan();
    //Error_Handler();
  } else {
    ssd1306_show();
  }

#endif
  
  PRINTF("Init Done\r\n");
}

/******************************************************************************/
/* board loop function */

void BOARD_Loop() {

  int tick_task_1 = HAL_GetTick();
  int tick_led = HAL_GetTick();

  while (1)
  {

#ifdef CONFIG_TASK1
    if((HAL_GetTick() - tick_task_1) >= CONFIG_TASK1_TIME_MS) {
      tick_task_1 = HAL_GetTick();
      task_1();
    }
#endif

#ifdef CONFIG_LED_NORMAL
    if((HAL_GetTick() - tick_led) >= CONFIG_LED_NORMAL_BLINK_MS) {
      tick_led = HAL_GetTick();
      HAL_GPIO_TogglePin(CONFIG_LED_NORMAL_PORT, CONFIG_LED_NORMAL_PIN);
    }
#endif

  }
}


