#include "led.h"
#include "os_timer.h"

#define OS_MAX_PENDING_DISPATCH_CALLS		16

static unsigned char os_pendentDispatchCalls = 0;

static void Task_1ms(void);
static void Task_5ms(void);
static void Task_10Ams(void);
static void Task_10Bms(void);
static void Task_10Cms(void);
static void OS_Dispatcher(void);

void OS_Task(void)
{
	if(os_pendentDispatchCalls > (unsigned char)0)
	{
		--os_pendentDispatchCalls;
		OS_Dispatcher();
	}
}

void OS_AddDispatchCall(void)
{
	if(os_pendentDispatchCalls <= OS_MAX_PENDING_DISPATCH_CALLS )
	{
		os_pendentDispatchCalls++;
	}
}

static void OS_Dispatcher(void)
{
	static unsigned char taskCnt = 0;

	switch (taskCnt)
	{
		  case 2:
		  	   Task_10Ams();
		  break;

		  case 4:
			Task_10Bms();
		  break;

		  case 5:
		  	   Task_5ms();
		  break;

		  case 9:
		  	taskCnt = 0;
			Task_5ms();
			Task_10Cms();
		  break;
	}
	Task_1ms();
	++taskCnt;	
}

void OS_Init(void)
{
	NVIC_Configuration();  
	TIM_Configuration(1);
}

void Task_Init(void)
{
	OS_Init();
	InitLED();
}

static void Task_1ms(void)
{
	
}

static void Task_5ms(void)
{

}

static void Task_10Ams(void)
{
	LED_Task();
}

static void Task_10Bms(void)
{

}

static void Task_10Cms(void)
{

}

