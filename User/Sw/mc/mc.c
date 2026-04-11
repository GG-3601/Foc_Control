/*Motor Control，电机控制*/
#include "mc.h"


void Mc_If_Init(void)
{

}

/*
// 假设你使用的 PWM 配置
#define PWM_PERIOD    800    // 根据你的 MCU 修改

void Mc_If_Poll(void)
{
    // 局部变量
    static q31_t theta;
     q31_t Id, Iq;
     q31_t alpha, beta;
     q31_t Ua, Ub, Uc;
     q31_t sin_theta, cos_theta;
     uint16_t pwm_a, pwm_b, pwm_c;

    // ==============================
    // 1. 输入：电角度（可从编码器/模拟器获取）
    // 这里示例：theta 可以是外部传入，或自增
    // ==============================

    // theta = Rte_If_ReadData(RteActualAngleIdx); //

    theta += Udsp_FloatToQ31(5.5f / 360.0f);  // 更慢

    if(theta > Udsp_FloatToQ31(1.0f)) 
    {
        theta = Udsp_FloatToQ31(-1.0f);
    }


    // ==============================
    // 2. 开环给定：Id=0，Iq=固定电压
    // ==============================
    Id = Udsp_FloatToQ31(0.0f);
    Iq = Udsp_FloatToQ31(0.11f);    // 开环电压，0.3 适合测试


    // ==============================
    // 3. CMSIS-DSP 原生：计算 sin / cos
    // ==============================
    sin_theta = arm_sin_q31(theta);
    cos_theta = arm_cos_q31(theta);


    // ==============================
    // 4. CMSIS-DSP 原生：反 Park 变换
    // ==============================
    arm_inv_park_q31(Id, Iq, &alpha, &beta, sin_theta, cos_theta);


    // ==============================
    // 5. CMSIS-DSP 原生：反 Clarke 变换
    // ==============================
    arm_inv_clarke_q31(alpha, beta, &Ua, &Ub);


    // ==============================
    // 6. CMSIS-DSP 原生：计算 Uc = -Ua - Ub
    // ==============================
    arm_negate_q31(&Ua, &Ua, 1);
    arm_negate_q31(&Ub, &Ub, 1);
    arm_add_q31(&Ua, &Ub, &Uc, 1);


    // ==============================
    // 7. 定点数转 PWM 占空比
    // ==============================
    pwm_a = ((int32_t)Ua >> 22) + (PWM_PERIOD / 2);
    pwm_b = ((int32_t)Ub >> 22) + (PWM_PERIOD / 2);
    pwm_c = ((int32_t)Uc >> 22) + (PWM_PERIOD / 2);


    // ==============================
    // 8. 输出到 3 路 PWM
    // （根据你的 MCU 平台修改寄存器或 HAL 库）
    // ==============================
    Tim_If_SetPwmDuty(Tim1, TimChannel1, pwm_a);
    Tim_If_SetPwmDuty(Tim1, TimChannel2, pwm_b);
    Tim_If_SetPwmDuty(Tim1, TimChannel3, pwm_c);
}*/
    

// 假设你使用的 PWM 配置
#define PWM_PERIOD    800    // 根据你的 MCU 修改
// ⚠️ 替换成你电机实际极对数
#define POLE_PAIRS  7  
void Mc_If_Poll(void)
{
    static q31_t theta = 0;
    static q31_t Id, Iq;
    static q31_t alpha, beta;
    static q31_t Ua, Ub, Uc;
    static q31_t sin_theta, cos_theta;
    static uint16_t pwm_a, pwm_b, pwm_c;

    static q31_t MechAngle = 0;    //机械角度
    static q31_t EleAngle  = 0;    //电角度

    Id = Udsp_FloatToQ31(0.0f);
    Iq = Udsp_FloatToQ31(0.05f);

    
    theta += Udsp_FloatToQ31(1.0f / 180.0f);

    // MechAngle = Rte_If_ReadData(RteActualAngleIdx);      //从RTE读取实际角度，单位为Q31格式，基准为360°
    // EleAngle  = Udsp_Abs_q31(MechAngle * POLE_PAIRS);    //电角度 = 机械角度 * 极对数
    // theta     = EleAngle;                                //将电角度赋值给theta

// uint32_t temp = (uint32_t)MechAngle * POLE_PAIRS;
// theta = (q31_t)(temp & 0x7FFFFFFF);


    /*sin / cos*/
    sin_theta = arm_sin_q31(theta);
    cos_theta = arm_cos_q31(theta);


    /*反 Park 变换*/
    arm_inv_park_q31(Id, Iq, &alpha, &beta, sin_theta, cos_theta);



    /*反 Clarke 变换*/
    arm_inv_clarke_q31(alpha, beta, &Ua, &Ub);


    // ==============================
    // 6. 计算 Uc = -Ua - Ub
    // ❗不能破坏 Ua / Ub 原值
    // ==============================
    q31_t neg_Ua, neg_Ub;

    arm_negate_q31(&Ua, &neg_Ua, 1);
    arm_negate_q31(&Ub, &neg_Ub, 1);
    arm_add_q31(&neg_Ua, &neg_Ub, &Uc, 1);


    // ==============================
    // 7. Q31 → PWM 映射
    // [-1,1) → [0, PWM_PERIOD]
    // ==============================
    pwm_a = (uint16_t)((((int64_t)Ua * PWM_PERIOD) >> 31) + (PWM_PERIOD / 2));
    pwm_b = (uint16_t)((((int64_t)Ub * PWM_PERIOD) >> 31) + (PWM_PERIOD / 2));
    pwm_c = (uint16_t)((((int64_t)Uc * PWM_PERIOD) >> 31) + (PWM_PERIOD / 2));


    // ==============================
    // 8. 限幅（防止溢出）
    // ==============================
    if(pwm_a > PWM_PERIOD) pwm_a = PWM_PERIOD;
    if(pwm_b > PWM_PERIOD) pwm_b = PWM_PERIOD;
    if(pwm_c > PWM_PERIOD) pwm_c = PWM_PERIOD;


    // ==============================
    // 9. 输出 PWM
    // ==============================
    Tim_If_SetPwmDuty(Tim1, TimChannel1, pwm_a);
    Tim_If_SetPwmDuty(Tim1, TimChannel2, pwm_b);
    Tim_If_SetPwmDuty(Tim1, TimChannel3, pwm_c);
}