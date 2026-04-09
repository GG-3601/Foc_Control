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

    Tim_If_PwmOutputEn();//测试
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
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
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
    q31_t inputA = 0x40000000; // Q31 格式的 0.5 (最大值 0x7FFFFFFF 代表 1.0)
    q31_t inputB = 0x20000000; // Q31 格式的 0.25
    q31_t output;

    // 调用 CMSIS-DSP 库函数进行乘法：0.5 * 0.25 = 0.125
    // 预期结果 output 应为 0x10000000
    arm_mult_q31(&inputA, &inputB, &output, 1);

    if (output == 0x10000000) {
        // 库函数运行正常！
        __NOP(); // 在这里打个断点
    }
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