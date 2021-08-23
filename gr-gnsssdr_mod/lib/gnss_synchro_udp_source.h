#ifndef GNSS_SYNCHRO_UDP_SOURCE_H
#define GNSS_SYNCHRO_UDP_SOURCE_H

#include "gnss_synchro.pb.h" // This file is created automatically by the Protocol Buffers compiler
#include <boost/asio.hpp>

class Gnss_Synchro_Udp_Source
{
public:
    Gnss_Synchro_Udp_Source(uint16_t port);

    // reads as many items as available, return number
    //[[deprecated("function blocks too long and doesn't hand back to block..")]] int
    //read_gnss_synchro(std::vector<gnss_sdr::Observables>& stocks);

    // returns one stock item
    bool read_gnss_synchro(gnss_sdr::Observables& stocks);

private:
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket;
    boost::system::error_code error;
    boost::asio::ip::udp::endpoint endpoint;
};

#endif // GNSS_SYNCHRO_UDP_SOURCE_H
