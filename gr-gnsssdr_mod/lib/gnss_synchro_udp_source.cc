#include "gnss_synchro_udp_source.h"
#include <sstream>


Gnss_Synchro_Udp_Source::Gnss_Synchro_Udp_Source(uint16_t port)
    : socket{ io_service }, endpoint{ boost::asio::ip::udp::v4(), port }
{
    socket.open(endpoint.protocol(), error); // Open socket.
    socket.bind(endpoint, error); // Bind the socket to the given local endpoint.
}

/*int Gnss_Synchro_Udp_Source::read_gnss_synchro(std::vector<gnss_sdr::Observables>& stocks)
{
    int nread = 0;
    while (true) {
        gnss_sdr::Observables tmp;
        if (!read_gnss_synchro(tmp)) {
            std::cout << "failed to read stock\n";
            break;
        } else {
            stocks.emplace_back(tmp);
            std::cout << "read stock\n";
            nread++;
        }
    }

    for (auto& stock : stocks) {
    }
    return nread;
}*/

bool Gnss_Synchro_Udp_Source::read_gnss_synchro(gnss_sdr::Observables& stocks)
{
    char buff[1500]; // Buffer for storing the received data.

    // TODO add timeout as in https://stackoverflow.com/a/51850018
    // This call will block until one or more bytes of data has been received.
    int bytes = socket.receive(boost::asio::buffer(buff));

    std::string data(&buff[0], bytes);
    // Deserialize a stock of Gnss_Synchro objects from the binary string.
    return stocks.ParseFromString(data);
}
