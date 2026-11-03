#include "rtc_bus_wrapper.h"

RtcBusWrapper::RtcBusWrapper(sc_module_name name)
    : sc_module(name), socket("socket")
{
    socket.register_b_transport(this, &RtcBusWrapper::b_transport);
}

void RtcBusWrapper::b_transport(tlm::tlm_generic_payload& gp, sc_time& delay) {
    /* addr 已是相对 RTC_BLOCK_OFFSET 的偏移（上层路由减过） */
    uint32_t  off  = (uint32_t)gp.get_address();
    uint32_t* data = reinterpret_cast<uint32_t*>(gp.get_data_ptr());

    if (!m_model.is_valid(off)) {
        gp.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
        return;
    }

    if (gp.get_command() == tlm::TLM_WRITE_COMMAND) {
        m_model.set(off, *data);
    } else if (gp.get_command() == tlm::TLM_READ_COMMAND) {
        *data = m_model.get(off);
    }

    gp.set_response_status(tlm::TLM_OK_RESPONSE);
    delay += sc_time(10, SC_NS);
}
