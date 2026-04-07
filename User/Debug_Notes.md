# 开发故障记录本 (Troubleshooting)

---

## [问题 ID] I2C 读数异常
- **日期**: 2026-04-07
- **现象**: `HAL_I2C_Master_Receive` 读取值为 0，但逻辑分析仪显示波形正常。

### 1. 原因分析
> 怀疑是 Stop 后紧跟 Start 导致从机状态重置，或 HAL 库状态未刷新。

### 2. 核心代码
```c
// 错误写法
HAL_I2C_Master_Transmit(...);
HAL_I2C_Master_Receive(...);

// 正确写法
HAL_I2C_Mem_Read(...);