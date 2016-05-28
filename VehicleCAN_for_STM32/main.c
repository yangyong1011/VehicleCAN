/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void InactiveLED(void);
static void ActiveLED(void);
static void LED_Task(void);
static void InitLED(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	SystemInit();
	InitLED();

	while (1)
	{
		LED_Task();
	}
}

static void InitLED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOA and GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	/*GPIOB Configuration: TIM3 channel1, 2, 3 and 4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE , GPIO_Pin_9);
	GPIO_SetBits(GPIOE , GPIO_Pin_11);
	GPIO_SetBits(GPIOE , GPIO_Pin_13);
	GPIO_SetBits(GPIOE , GPIO_Pin_14);
}

static void InactiveLED(void)
{
	GPIO_SetBits(GPIOE , GPIO_Pin_14);
}

static void ActiveLED(void)
{
	GPIO_ResetBits(GPIOE , GPIO_Pin_14);
}

static void LED_Task(void)
{
	static unsigned int cnt = 0;
	static unsigned char flag = 0;
	cnt++;
	if (cnt > 0xfff0)
	{
		cnt = 0;
		if (flag == 0)
		{
			ActiveLED();
			flag = 1;
		}
		else
		{
			InactiveLED();
			flag = 0;
		}
		
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
