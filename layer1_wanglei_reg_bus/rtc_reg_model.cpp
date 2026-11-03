#include "rtc_reg_model.h"

RtcRegModel::RtcRegModel() { reset(); }

void RtcRegModel::reset() {
    for (uint32_t i = 0; i < RTC_REG_NUM; i++) {
        m_reg[i] = RTC_RESET_ALL;
    }
}

uint32_t RtcRegModel::idx_of(uint32_t off) const { return off / 4; }

bool RtcRegModel::is_reserved(uint32_t idx) const {
    return (idx == 7) || (idx == 15);
}

bool RtcRegModel::is_valid(uint32_t off) const {
    if (off % 4 != 0) return false;
    uint32_t idx = idx_of(off);
    if (idx >= RTC_REG_NUM) return false;
    if (is_reserved(idx)) return false;
    return true;
}

uint32_t RtcRegModel::get(uint32_t off) const {
    if (!is_valid(off)) return 0;
    return m_reg[idx_of(off)];
}

void RtcRegModel::set(uint32_t off, uint32_t v) {
    if (!is_valid(off)) return;
    m_reg[idx_of(off)] = v;
}

void RtcRegModel::set_bits(uint32_t off, uint32_t mask) {
    if (!is_valid(off)) return;
    m_reg[idx_of(off)] |= mask;
}

void RtcRegModel::clr_bits(uint32_t off, uint32_t mask) {
    if (!is_valid(off)) return;
    m_reg[idx_of(off)] &= ~mask;
}
