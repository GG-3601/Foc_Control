/*任务管理系统，Task Management System*/
#include "tms.h"

static void Tms_Task_Init(void);
static void Tms_Task_1ms(void);
static void Tms_Task_10ms(void);
static void Tms_Task_50ms(void);
static void Tms_Task_100ms(void);
static void Tms_Task_500ms(void);
static void Tms_Task_1000ms(void);
static void Tms_Task_Idle(void);


/*初始化*/
void Tms_If_Init(void)
{
    Tms_Task_Init();
}

/*轮询*/
void Tms_If_Poll(void) 
{
    static uint32_t LastTick = 0;
    uint32_t CurrentTick = HAL_GetTick();

    /*确保 1ms 只进入一次逻辑*/
    if (CurrentTick != LastTick) 
    {
        LastTick = CurrentTick;
        
        /*1ms任务*/
        Tms_Task_1ms();

        /*10ms任务*/
        if (CurrentTick % 10 == 0) 
        {
            Tms_Task_10ms();
        }

        /*50ms任务*/
        if (CurrentTick % 50 == 0) 
        {
            Tms_Task_50ms();
        }
        /*100ms任务*/
        if (CurrentTick % 100 == 0) 
        {
            Tms_Task_100ms();
            
        }
        /*500ms任务*/
        if (CurrentTick % 500 == 0) 
        {
            Tms_Task_500ms();
            
        }

        /*1000ms (1s) 任务*/
        if (CurrentTick % 1000 == 0) 
        {
            Tms_Task_1000ms();
        }
    }

    /*空闲任务*/
    Tms_Task_Idle();
}

/*初始化任务*/
static void Tms_Task_Init(void)
{
    FMSTR_Init();
    
}

/*1ms任务*/
static void Tms_Task_1ms(void) 
{
    
}

/*10ms任务*/
static void Tms_Task_10ms(void)
{

}

/*50ms任务*/
static void Tms_Task_50ms(void)
{
    static uint8_t LedState = 0;
    if(LedState == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    }
}

/*100ms任务*/
static void Tms_Task_100ms(void)
{
    As_If_Poll();
}

/*500ms任务*/
static void Tms_Task_500ms(void)
{

}

/*1000ms (1s) 任务*/
static void Tms_Task_1000ms(void)
{

}

/*空闲任务*/
static void Tms_Task_Idle(void)
{
    FMSTR_Poll();
}