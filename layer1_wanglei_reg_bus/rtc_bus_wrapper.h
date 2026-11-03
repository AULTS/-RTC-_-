#ifndef RTC_BUS_WRAPPER_H
#define RTC_BUS_WRAPPER_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include "rtc_reg_defs.h"
#include "rtc_reg_model.h"

/* ============================================================
 * 角色1 基础层：总线适配外壳（TLM target）
 * 只把 b_transport 转发给 RtcRegModel，不含任何业务逻辑
 * 本阶段不接 SystemTop，由 top_integrate 集成时绑定
 * ============================================================ */
SC_MODULE(RtcBusWrapper) {
public:
    tlm_utils::simple_target_socket<RtcBusWrapper> socket;

    RtcBusWrapper(sc_module_name name);

    /* 给角色2/3/4：绕过总线直接拿模型（单元自测用） */
    RtcRegModel& regs() { return m_model; }

private:
    RtcRegModel m_model;
    void b_transport(tlm::tlm_generic_payload& gp, sc_time& delay);
};

#endif
