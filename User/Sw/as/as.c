/*角度传感器，angle sensor*/
#include "as.h"

static void As_ReadAngle(void);


uint8_t AsRegAddr[AsRegAddrIndexMax] = 
{
    [AsAngleAddrIndex] = 0x0E,  //角度寄存器地址
};

void As_If_Init(void)
{

}

void As_If_Poll(void)
{
    As_ReadAngle();
}

/*读取角度数据*/
static void As_ReadAngle(void)
{
    static uint32_t Angle = 0;  //测试
    uint8_t RxData[2] = {0};

    /*写入寄存器地址*/
    I2c_If_Transmit(I2c1, AS_SLAVE_ADDR, &AsRegAddr[AsAngleAddrIndex], 1);

    /*读取角度数据*/
    I2c_If_Receive(I2c1, AS_SLAVE_ADDR, &RxData[0], 2);

    Angle = (uint16_t)((RxData[0] << 8) | RxData[1]);
    Angle = Angle * AS_ANGLE_MAX / 4095;

    Rte_If_WriteData(RteActualAngleIdx, &Angle);

}