#ifndef RTC_REG_MODEL_H
#define RTC_REG_MODEL_H

#include <stdint.h>
#include "rtc_reg_defs.h"

/* ============================================================
 * 角色1 基础层：纯 C++ 寄存器模型，零 SystemC 依赖
 * 只做"格子存取 + 复位 + 合法性"，不含计时/闹钟/中断逻辑
 * 角色2/3/4 直接调用 get()/set() 即可，无需等总线层就绪
 * ============================================================ */
class RtcRegModel {
public:
    RtcRegModel();

    void     reset();                        /* 上电全 0 */
    bool     is_valid(uint32_t off) const;   /* 对齐 + 范围内 + 非保留空洞 */
    uint32_t get(uint32_t off) const;        /* 读，非法返回 0 */
    void     set(uint32_t off, uint32_t v);  /* 写，非法忽略 */

    /* 位操作辅助（仍只存取，不做任何判断） */
    void     set_bits(uint32_t off, uint32_t mask);
    void     clr_bits(uint32_t off, uint32_t mask);

private:
    uint32_t m_reg[RTC_REG_NUM];
    uint32_t idx_of(uint32_t off) const;
    bool     is_reserved(uint32_t idx) const;  /* 索引 7(0x1C) / 15(0x3C) */
};

#endif
