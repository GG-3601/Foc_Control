#include "freemaster_uart_user.h"

static FMSTR_BOOL Fm_Uart_Init(void);
static void Fm_Uart_EnableTransmit(FMSTR_BOOL enable);
static void Fm_Uart_EnableReceive(FMSTR_BOOL enable);
FMSTR_BOOL Fm_Uart_IsTransmitRegEmpty(void);
FMSTR_BOOL Fm_Uart_IsReceiveRegFull(void);
FMSTR_BOOL Fm_Uart_IsTransmitterActive(void);
void Fm_Uart_PutChar(FMSTR_BCHR ch);
FMSTR_BCHR Fm_Uart_GetChar(void);
void Fm_Uart_Flush(void);

extern UART_HandleTypeDef huart1;  //声明外部UART句柄

const FMSTR_SERIAL_DRV_INTF FmUartDrv = 
{
    .Init                = Fm_Uart_Init,
    .EnableTransmit      = Fm_Uart_EnableTransmit,
    .EnableReceive       = Fm_Uart_EnableReceive,
    .IsTransmitRegEmpty  = Fm_Uart_IsTransmitRegEmpty,
    .IsReceiveRegFull    = Fm_Uart_IsReceiveRegFull,
    .IsTransmitterActive = Fm_Uart_IsTransmitterActive,
    .PutChar             = Fm_Uart_PutChar,
    .GetChar             = Fm_Uart_GetChar,
    .Flush               = Fm_Uart_Flush,
    
};


/*初始化*/
static FMSTR_BOOL Fm_Uart_Init(void)
{
    return FMSTR_TRUE;  //uart初始化在main函数中完成，这里直接返回成功
} 


/*使能发送*/
static void Fm_Uart_EnableTransmit(FMSTR_BOOL enable)
{
    //uart初始化后默认一直开启
}

/*使能接收*/
static void Fm_Uart_EnableReceive(FMSTR_BOOL enable)
{
    //uart初始化后默认一直开启
}

/*判断发送寄存器是否为空*/
FMSTR_BOOL Fm_Uart_IsTransmitRegEmpty(void)
{
    return (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) != RESET) ? FMSTR_TRUE : FMSTR_FALSE;
}


/*判断接收寄存器是否为满*/
FMSTR_BOOL Fm_Uart_IsReceiveRegFull(void)
{
    return (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET) ? FMSTR_TRUE : FMSTR_FALSE;
}

/*判断发送器是否正在发送*/
FMSTR_BOOL Fm_Uart_IsTransmitterActive(void)
{
    return (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET) ? FMSTR_TRUE : FMSTR_FALSE;
}

/*发送字符*/
void Fm_Uart_PutChar(FMSTR_BCHR ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
}

/*接收字符*/
FMSTR_BCHR Fm_Uart_GetChar(void)
{
    uint8_t ch;
    HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
    return (FMSTR_BCHR)ch;
}


/*刷新UART缓冲区*/
void Fm_Uart_Flush(void)
{
    while(!(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC)))
    {
        //在这里可以加一个简单的计数超时，防止硬件出错导致死循环
    }
}