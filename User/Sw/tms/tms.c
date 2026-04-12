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

    Tim_If_TimerEn(Tim2);    //使能定时器2，作为TMS的时间基准
}

/*轮询*/
void Tms_If_Poll(void) 
{
    static   uint32_t LastTick = 0;
    uint32_t CurrentTick       = HAL_GetTick();
    uint32_t TimStartTick      = 0;
    uint32_t TimEndTick        = 0;
    static uint32_t TimElapsedTicks   = 0;                // 计算的经过的计数，测试
    uint32_t TimLoadRatio      = 0;                // 计算的负载率

    /*获取定时器2的计数*/
    TimStartTick = __HAL_TIM_GET_COUNTER(&htim2);

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

    /*计算负载率*/
    TimEndTick = __HAL_TIM_GET_COUNTER(&htim2);
    if( TimEndTick >= TimStartTick)
    {
        TimElapsedTicks = TimEndTick - TimStartTick;
    }
    else
    {
        TimElapsedTicks = (0xFFFF - TimStartTick) + TimEndTick + 1; // 处理计数器溢出情况
    }
    TimLoadRatio = TimElapsedTicks*100/1000;    // 计算负载率，单位%
    Rte_If_WriteData(Rte_Tms_LoadRatioIdx, &TimLoadRatio);    //将负载率写入RTE

}

/*初始化任务*/
static void Tms_Task_Init(void)
{
    
    FMSTR_Init(); 
    Mc_If_Init();

}

/*1ms任务*/
static void Tms_Task_1ms(void) 
{
    Mc_If_Poll(); //测试
    
}

/*10ms任务*/
static void Tms_Task_10ms(void)
{

}

/*50ms任务*/
static void Tms_Task_50ms(void)
{
    As_If_Poll(); 

}

/*100ms任务*/
static void Tms_Task_100ms(void)
{

}

/*500ms任务*/
static void Tms_Task_500ms(void)
{
    static uint8_t LedState = 1;
    if(LedState == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
    }
    
}

/*1000ms (1s) 任务*/
static void Tms_Task_1000ms(void)
{

}

/*空闲任务*/
static void Tms_Task_Idle(void)
{
    FMSTR_Poll();   //每次轮询耗时约3μs

    // uint32_t TimStartTick = __HAL_TIM_GET_COUNTER(&htim2);
    // FMSTR_Poll();
    // uint32_t TimEndTick = __HAL_TIM_GET_COUNTER(&htim2);
    // static uint32_t TimElapsedTicks = 0;
    // if (TimEndTick >= TimStartTick)
    // {
    //     TimElapsedTicks = TimEndTick - TimStartTick;
    // }
    // else
    // {
    //     TimElapsedTicks = (0xFFFFFFFF - TimStartTick) + TimEndTick + 1; // 处理计数器溢出情况
    // }
}