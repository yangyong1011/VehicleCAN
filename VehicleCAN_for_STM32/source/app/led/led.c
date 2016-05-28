#include "stm32f10x_gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void InactiveLED(void);
static void ActiveLED(void);

void InitLED(void)
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

void LED_Task(void)
{
	static unsigned int cnt = 0;
	static unsigned char flag = 0;
	cnt++;
	if (cnt > 100)
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

