#ifndef SPONGE_LIBSPONGE_TCP_STATE
#define SPONGE_LIBSPONGE_TCP_STATE

#include "tcp_receiver.hh"
#include "tcp_sender.hh"

#include <string>

//! \brief Summary of a TCPConnection's internal state
//!
//! Most TCP implementations have a global per-connection state
//! machine, as described in the [TCP](\ref rfc::rfc793)
//! specification. Sponge is a bit different: we have factored the
//! connection into two independent parts (the sender and the
//! receiver). The TCPSender and TCPReceiver maintain their interval
//! state variables independently (e.g. next_seqno, number of bytes in
//! flight, or whether each stream has ended). There is no notion of a
//! discrete state machine or much overarching state outside the
//! sender and receiver. To test that Sponge follows the TCP spec, we
//! use this class to compare the "official" states with Sponge's
//! sender/receiver states and two variables that belong to the
//! overarching TCPConnection object.
class TCPState {
  public:
    //! \brief Summarize the state of a TCPReceiver in a string
    static std::string state_summary(const TCPReceiver &receiver);

    //! \brief Summarize the state of a TCPSender in a string
    static std::string state_summary(const TCPSender &receiver);
};

namespace TCPReceiverStateSummary {
const std::string ERROR = "error (connection was reset)";
const std::string LISTEN = "waiting for stream to begin (listening for SYN)";
const std::string SYN_RECV = "stream started";
const std::string FIN_RECV = "stream finished";
}  // namespace TCPReceiverStateSummary

namespace TCPSenderStateSummary {
const std::string ERROR = "error (connection was reset)";
const std::string CLOSED = "waiting for stream to begin (no SYN sent)";
const std::string SYN_SENT = "stream started but nothing acknowledged";
const std::string SYN_ACKED = "stream ongoing";
const std::string FIN_SENT = "stream finished (FIN sent) but not fully acknowledged";
const std::string FIN_ACKED = "stream finished and fully acknowledged";
}  // namespace TCPSenderStateSummary

#endif  // SPONGE_LIBSPONGE_TCP_STATE
