#include <cstdio>
#include "rtc_reg_model.h"
#include "rtc_reg_defs.h"

static int g_fail = 0;
static void check(bool ok, const char* what) {
    std::printf("[%s] %s\n", ok ? "PASS" : "FAIL", what);
    if (!ok) g_fail++;
}

int main() {
    RtcRegModel m;

    check(m.get(RTC_REG_SEC)  == 0, "reset SEC = 0");
    check(m.get(RTC_REG_CTRL) == 0, "reset CTRL = 0");

    m.set(RTC_REG_SEC, 42);
    check(m.get(RTC_REG_SEC) == 42, "write/read SEC = 42");

    m.set(RTC_REG_ALARM_MIN, 7);
    check(m.get(RTC_REG_ALARM_MIN) == 7, "role3 ALARM_MIN = 7");
    check(m.get(RTC_REG_SEC) == 42,       "SEC unchanged after ALARM write");
    m.set(RTC_REG_CALIB, 0x5A);
    check(m.get(RTC_REG_CALIB) == 0x5A,   "role4 CALIB = 0x5A");

    m.set_bits(RTC_REG_CTRL, RTC_CTRL_EN);
    check((m.get(RTC_REG_CTRL) & RTC_CTRL_EN) != 0, "set_bits CTRL_EN");
    m.clr_bits(RTC_REG_CTRL, RTC_CTRL_EN);
    check((m.get(RTC_REG_CTRL) & RTC_CTRL_EN) == 0, "clr_bits CTRL_EN");

    m.set(0x02, 99);  check(m.get(0x02) == 0, "unaligned off ignored");
    m.set(0x48, 99);  check(m.get(0x48) == 0, "out-of-range ignored");
    m.set(0x1C, 99);  check(m.get(0x1C) == 0, "reserved hole idx7 ignored");
    m.set(0x3C, 99);  check(m.get(0x3C) == 0, "reserved hole idx15 ignored");

    m.reset();
    check(m.get(RTC_REG_SEC) == 0, "reset clears SEC");

    std::printf("\n=== %s ===\n", g_fail ? "FAILED" : "ALL PASS");
    return g_fail ? 1 : 0;
}
