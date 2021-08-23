#ifndef GNSS_PVT_UDP_SOURCE_H
#define GNSS_PVT_UDP_SOURCE_H

#include "monitor_pvt.pb.h" // This file is created automatically by the Protocol Buffers compiler
#include <boost/asio.hpp>
#include <vector>

class Gnss_Pvt_Udp_Source
{
public:
    Gnss_Pvt_Udp_Source(uint16_t port);

    // returns one stock item
    bool read_pvt_monitor(gnss_sdr::PvtMonitorMsgs& msgs);

private:
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket;
    boost::system::error_code error;
    boost::asio::ip::udp::endpoint endpoint;
};

#endif // GNSS_PVT_UDP_SOURCE_H
