# 王磊（基础层）交付说明

## 我负责
- common/        ：全员引用的公共头文件
- layer1_reg_bus/：RTC 寄存器模型 + 总线封装 + 单元自测
- 其余目录为空壳占位，由对应角色维护

## 当前交付内容
- common/rtc_reg_defs.h：全寄存器偏移 / 位域宏 / 复位默认值
- common/rtc_time.h    ：统一时间结构体与全局常量
- layer1_reg_bus/      ：寄存器读写模型、get(off)/set(off,v) 接口

## 全员统一约定（重要）
1. 一律在工程根目录 ~/rtc_l6_systemc/ 下执行编译命令
2. 头文件统一写 #include "rtc_reg_defs.h"，编译统一加 -Icommon
3. 源码里禁止出现 C:/msys64/home/xxx 这类绝对路径
4. rtc_reg_defs.h 由角色1 冻结，要改先找我，不要各自复制一份改

## 引用示例
  g++ -c layer2_core_timer/xxx.cpp -Icommon -I"C:/systemc/include" -std=c++17

## 分工
- 秒进位 / 闰年 / 分频 / L6 时间同步 → 角色2
- 闹钟匹配 / 中断置位与清除 / 接 GIC → 角色3
- 掉电保持 / 低功耗 / 校准 → 角色4
- 上层 API / 集成测试 → 角色5

## 自检
  cd ~/rtc_l6_systemc
  grep -n "RTC_REG_SEC\|RTC_REG_IRQ_STAT\|RTC_BLOCK_OFFSET" common/rtc_reg_defs.h

## 总线层（3B）编译示例
  g++ -c layer1_reg_bus/rtc_bus_wrapper.cpp -Icommon -Ilayer1_reg_bus -I"C:/systemc/include" -std=c++17

## 边界补充
- rtc_bus_wrapper 只预留 target socket，集成由 top_integrate 负责
- 本层不声明 irq 引脚（角色3 负责），避免出现未绑定端口
