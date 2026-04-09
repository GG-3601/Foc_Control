/*角度传感器，angle sensor*/
#include "as.h"

static void As_ReadAngle(void);


uint16_t AsRegAddr[AsRegAddrIndexMax] = 
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
    q31_t Angle = 0;  
    uint8_t RxData[2] = {0};
    I2cRxTxCfg_t I2cRxTxCfg = 
    {
        .I2cChanl    = I2c1,
        .DevAddr     = AS_SLAVE_ADDR,
        .MemAddr     = AsRegAddr[AsAngleAddrIndex],
        .MemAddrSize = 1,
        .pData       = RxData,
        .Size        = 2,
    };

    I2c_If_ReadMem(&I2cRxTxCfg);

    Angle = (RxData[0] << 8) | RxData[1];    //将高8位和低8位组合成16位数据，有效为12位数据
    Angle = Angle << 19;                     //将12位数据左移19位，转换为Q31格式，基准为AS_ANGLE_MAX

    Rte_If_WriteData(RteActualAngleIdx, (uint32_t*)&Angle);
}