#ifndef RTC_REG_DEFS_H
#define RTC_REG_DEFS_H

#include <stdint.h>

/* ============================================================
 * 角色1 维护 | 全员引用
 * RTC 全量寄存器：地址映射 / 位域 / 复位默认值
 * 本文件只定义"格子"，不含任何计时、闹钟、中断逻辑
 * ============================================================ */

#define RTC_BLOCK_OFFSET   0x3000u   /* 与 top_integrate 约定，本阶段不写进 SystemTop */
#define RTC_REG_SPAN       0x1000u

/* 角色2：时间计数 */
#define RTC_REG_CTRL       0x00u
#define RTC_REG_SEC        0x04u
#define RTC_REG_MIN        0x08u
#define RTC_REG_HOUR       0x0Cu
#define RTC_REG_DAY        0x10u
#define RTC_REG_MON        0x14u
#define RTC_REG_YEAR       0x18u

/* 角色3：闹钟 + 中断 */
#define RTC_REG_ALARM_SEC  0x20u
#define RTC_REG_ALARM_MIN  0x24u
#define RTC_REG_ALARM_HOUR 0x28u
#define RTC_REG_ALARM_MASK 0x2Cu
#define RTC_REG_IRQ_STAT   0x30u   /* 写1清除 */
#define RTC_REG_IRQ_EN     0x34u

/* 角色4：校准 + 掉电保持 */
#define RTC_REG_CALIB      0x38u
#define RTC_REG_BKUP0      0x40u
#define RTC_REG_BKUP1      0x44u

#define RTC_REG_NUM        18u      /* 0x44/4=17，+1；索引7/15为保留空洞 */

/* ---- CTRL 位域 ---- */
#define RTC_CTRL_EN        (1u << 0)
#define RTC_CTRL_CLKSEL    (1u << 1)
#define RTC_CTRL_SWRST     (1u << 2)

/* ---- IRQ_STAT / IRQ_EN 共用位域 ---- */
#define RTC_IRQ_SEC        (1u << 0)
#define RTC_IRQ_ALARM      (1u << 1)
#define RTC_IRQ_OVF        (1u << 2)

#define RTC_RESET_ALL      0x00u    /* 上电全 0 */

#endif
