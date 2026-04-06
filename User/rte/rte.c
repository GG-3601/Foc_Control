#include "rte.h"

uint32_t RteData[RteIdxMax] = {0};



/*写入数据*/
void Rte_If_WriteData(RteDataIdx_t Idx, uint32_t* pData)
{
    if (Idx < RteIdxMax)
    {
        RteData[Idx] = *pData;
    }
}

/*读取数据*/
uint32_t Rte_If_ReadData(RteDataIdx_t Idx)
{
    return RteData[Idx];
}

