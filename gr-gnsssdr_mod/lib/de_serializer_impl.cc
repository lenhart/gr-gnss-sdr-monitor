/* -*- c++ -*- */
/*
 * Copyright 2021 Malte Lenhart.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "de_serializer_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace gnsssdr_mod {

de_serializer::sptr de_serializer::make(uint16_t port_monitor, uint16_t port_pvt)
{
    return gnuradio::get_initial_sptr(new de_serializer_impl(port_monitor, port_pvt));
}


/*
 * The private constructor
 */
de_serializer_impl::de_serializer_impl(uint16_t port_monitor, uint16_t port_pvt)
    : gr::block("de_serializer",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)), // have message output instead
      b_port_monitor(port_monitor),
      b_port_pvt(port_pvt)
{
    message_port_register_out(pmt::mp("out"));

    //start();
    // with pmt::pmt_t message_ports_out(); we can query our-ports
}

// function to test message passing. works. now we need better data
void de_serializer_impl::test_msg_passing() {
	constexpr int n_output_types = 3;
	     for (int i = 0; i < 5; i++) {
	         std::string foo = "output " + std::to_string(i);
	         message_port_pub(pmt::mp("out"), pmt::mp(foo));
	         std::this_thread::sleep_for(std::chrono::seconds(1));
	     }
}

void de_serializer_impl::run()
{
    float* out;
    // initialize reading fcts as threadshic

    test_msg_passing();

    while(!d_finished) {
		gnss_sdr::Observables stocks;
		bool success = gnss_sync_src_sptr->read_gnss_synchro(stocks);
		if (success) {
			// TODO MOVE TO POSTPROCESSING
			std::map<int, gnss_sdr::GnssSynchro> channels;

			populate_monitor_channels(stocks, channels);
			print_table(channels); // TODO REPLACE BY ACTUAL PASSING OUT TO NEXT BLOCK

			// preparing for output
			//process(stocks, out);
		}

		// realign based on iTOW msg

		// gnss_sdr::PvtMonitorMsgs msgs;
		// bool success_pvt = gnss_pvt_src_sptr->read_pvt_monitor(msgs);
		// TODO DO STH


		// output message
		// message_port_pub(pmt::mp("out"), pmt::mp(foo));
    }
}

/*
 * Our virtual destructor.
 */
de_serializer_impl::~de_serializer_impl()
{
    gr::thread::scoped_lock d_mutex;
    d_finished = true;
    d_thread.join();
}

bool de_serializer_impl::start()
{
	std::cout << __func__ << "start fct called\n";
	gnss_sync_src_sptr = std::make_shared<Gnss_Synchro_Udp_Source>(b_port_monitor);
    gnss_pvt_src_sptr = std::make_shared<Gnss_Pvt_Udp_Source>(b_port_pvt);

    std::cout << std::setw(3) << "CH" << std::setw(6) << "PRN" << std::setw(14)
              << "CN0 [dB-Hz]" << std::setw(17) << "Doppler [Hz]\n"
              << '\n';

    d_thread = std::thread(&de_serializer_impl::run, this);


    return true;
}

/**
 * what we need:
 *  - Carrier_Doppler_hz    // doppler estimation
    - Carrier_phase_rads    // carrier phase estimation
    - Code_phase_samples    // code phase
 */

void de_serializer_impl::process(const gnss_sdr::Observables& stocks, float* out)
{
    // output interleaved tagged stream [prn, value]
    // first foi:
    for (size_t i = 0; i < stocks.observable_size(); i++) {
        gnss_sdr::GnssSynchro ch = stocks.observable(i);
        for (int i = 0; i < 3; i++) {
            // out[i][0] = ch.prn(); // todo think about indices
            // out[i][1] = ch.carrier_doppler_hz();
        }
    }
}

void de_serializer_impl::populate_monitor_channels(
    const gnss_sdr::Observables& stocks, std::map<int, gnss_sdr::GnssSynchro>& channels)
{
    for (std::size_t i = 0; i < stocks.observable_size(); i++) {
        gnss_sdr::GnssSynchro ch = stocks.observable(i);
        if (ch.fs() != 0) // Channel is valid.
        {
            channels[ch.channel_id()] = ch;
        }
    }
}

void de_serializer_impl::print_table(std::map<int, gnss_sdr::GnssSynchro>& channels)
{
    // Print table contents.
    for (auto const& ch : channels) {
        int channel_id = ch.first;              // Key
        gnss_sdr::GnssSynchro data = ch.second; // Value


        std::cout << std::setw(3) << channel_id << std::setw(6) << data.prn()
                  << std::setw(14) << data.cn0_db_hz() << std::setw(17)
                  << data.carrier_doppler_hz() << '\n';
    }
}


} /* namespace gnsssdr_mod */
} // namespace gr
