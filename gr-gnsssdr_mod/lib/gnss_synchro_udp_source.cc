#include "gnss_synchro_udp_source.h"
#include <sstream>


Gnss_Synchro_Udp_Source::Gnss_Synchro_Udp_Source(uint16_t port)
    : socket{ io_service }, endpoint{ boost::asio::ip::udp::v4(), port }
{
    socket.open(endpoint.protocol(), error); // Open socket.
    socket.bind(endpoint, error); // Bind the socket to the given local endpoint.
}

bool Gnss_Synchro_Udp_Source::read_gnss_synchro(gnss_sdr::Observables& stocks)
{
    char buff[1500]; // Buffer for storing the received data.

    // This call will block until one or more bytes of data has been received.
    int bytes = socket.receive(boost::asio::buffer(buff));

    std::string data(&buff[0], bytes);
    // Deserialize a stock of Gnss_Synchro objects from the binary string.
    return stocks.ParseFromString(data);
}
