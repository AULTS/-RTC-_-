#ifndef RTC_TIME_H
#define RTC_TIME_H

#include <stdint.h>
#include "rtc_reg_defs.h"

/* ============================================================
 * 角色1 维护 | 全员引用
 * 统一时间结构体 + 全局常量；不含任何进位/闰年/闹钟函数
 * ============================================================ */

/* 全员只准用这一个结构体，不要各自定义 struct time */
typedef struct {
    uint32_t sec;    /* 0-59  */
    uint32_t min;    /* 0-59  */
    uint32_t hour;   /* 0-23  */
    uint32_t day;    /* 1-31  */
    uint32_t mon;    /* 1-12  */
    uint32_t year;   /* 如 2026 */
} rtc_time_t;

/* ---- 进位边界（角色2 用）---- */
#define RTC_SEC_PER_MIN    60u
#define RTC_MIN_PER_HOUR   60u
#define RTC_HOUR_PER_DAY   24u
#define RTC_MON_PER_YEAR   12u

/* 平年各月天数表；闰年 2 月=29 由角色2 自行判断
 * 用 static const：头文件里每个编译单元各一份，无链接冲突 */
static const uint32_t RTC_DAYS_IN_MONTH[12] =
    { 31u,28u,31u,30u,31u,30u,31u,31u,30u,31u,30u,31u };

/* ---- 时间基准 / L6 时间同步粒度（角色2 关键依赖）---- */
#define RTC_TICK_NS            1000000000ull  /* 1Hz = 1 秒 */
#define RTC_L6_STEP_NS         1000ull        /* 与 QEMU 侧 SC_TICK_NS 一致 */
#define RTC_L6_STEPS_PER_SEC   (RTC_TICK_NS / RTC_L6_STEP_NS)  /* 1000000 */

/* 上电默认时间：与 RTC_RESET_ALL 一致（全 0）
 * 合法性校正由角色2/角色5 处理，这里不擅自填 1970 */
#define RTC_TIME_RESET  { 0u, 0u, 0u, 0u, 0u, 0u }

#endif
