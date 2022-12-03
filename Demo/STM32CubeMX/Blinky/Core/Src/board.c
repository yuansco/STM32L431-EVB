

#include "board.h"
#include "main.h"
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
/* board init function */

void BOARD_Init() {
  PRINTF("Ver: %s-%s\r\n", VERSION, BUILD_DATE);
  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
}

/******************************************************************************/
/* board loop function */

void BOARD_Loop() {

  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
  PRINTF("Demo LED BLUE:%d\r\n" ,HAL_GPIO_ReadPin(LED_BLUE_GPIO_Port, LED_BLUE_Pin));
  PRINTF("Demo LED RED:%d\r\n" ,HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin));

}

