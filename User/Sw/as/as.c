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
    uint32_t Angle = 0;  
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

    Angle = (uint16_t)((RxData[0] << 8) | RxData[1]);
    Angle = Angle * AS_ANGLE_MAX / 4095;

    Rte_If_WriteData(RteActualAngleIdx, &Angle);
}