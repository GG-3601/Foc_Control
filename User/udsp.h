/*User Digital Signal Processing Library, 用户重新包装的数字信号处理库*/
#ifndef __UDSP_H__
#define __UDSP_H__

#include "arm_math.h"

/*浮点数转Q31定点数*/
static inline q31_t Udsp_FloatToQ31(float32_t Data)
{
    q31_t Result;
    arm_float_to_q31(&Data, &Result, 1);
    return Result;
}

/*32位定点数加法 (Data1 + Data2)*/
static inline q31_t Udsp_Add_q31(q31_t Data1, q31_t Data2)
{
    q31_t Result;
    arm_add_q31(&Data1, &Data2, &Result, 1); 
    return Result;
}

/*32位定点数减法 (Data1 - Data2) */
static inline q31_t Udsp_Sub_q31(q31_t Data1, q31_t Data2)
{
    q31_t Result;
    arm_sub_q31(&Data1, &Data2, &Result, 1);
    return Result;
}

/*32位定点数乘法 (Data1 * Data2) */
static inline q31_t Udsp_Mult_q31(q31_t Data1, q31_t Data2)
{
    q31_t Result;
    arm_mult_q31(&Data1, &Data2, &Result, 1);
    return Result;
}

/*32位定点数绝对值 */
static inline q31_t Udsp_Abs_q31(q31_t Data)
{
    q31_t Result;
    arm_abs_q31(&Data, &Result, 1);
    return Result;
}


#endif /* __UDSP_H__ */