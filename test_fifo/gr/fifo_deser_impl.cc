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

#include <gnuradio/io_signature.h>
#include "fifo_deser_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
  namespace gnsssdr_mod {

    fifo_deser::sptr
    fifo_deser::make(const std::string fifo)
    {
      return gnuradio::get_initial_sptr
        (new fifo_deser_impl(fifo));
    }


    /*
     * The private constructor
     */
    fifo_deser_impl::fifo_deser_impl(const std::string fifo)
      : gr::block("fifo_deser",
              gr::io_signature::make(0, 0, sizeof(0)),
              gr::io_signature::make(0, 0, sizeof(0))), file_name(fifo)
    {
    	message_port_register_out(pmt::mp("out"));     // with pmt::pmt_t message_ports_out(); we can query our-ports

    	start();

    	d_thread = std::thread(&fifo_deser_impl::run, this);
    }

    bool fifo_deser_impl::start() {
        fifo.open(file_name, std::ios::binary);
        return fifo.is_open();
    }

    void fifo_deser_impl::run() {
    	char buffer[1500];

    	while (!d_finished) {
			std::string newline;
			std::getline(fifo, newline);
			//std::cout << items_retrieved << " bytes read" << std::endl;
			//int bytes = fifo.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
			//std::string data(&buffer[0], bytes);

			if(fifo.good()){
				gnss_sdr::Observables stocks;
				bool success = stocks.ParseFromString(newline);
				if (success) {
					std::map<int, gnss_sdr::GnssSynchro> channels;
					populate_monitor_channels(stocks, channels);
					print_table(channels);
				}
			} else if (fifo.eof()) {
				fifo.clear();
			} else {
				std::cout << __func__ << "unhandled even\n" << std::flush;
			}

    	}

    }

    /*
     * Our virtual destructor.
     */
    fifo_deser_impl::~fifo_deser_impl()
    {
        gr::thread::scoped_lock d_mutex;
        d_finished = true;
        d_thread.join();
    }

    void fifo_deser_impl::populate_monitor_channels(
        const gnss_sdr::Observables& stocks, std::map<int, gnss_sdr::GnssSynchro>& channels)
    {
    	std::cout << stocks.observable_size() << " nr items \n";
        for (std::size_t i = 0; i < stocks.observable_size(); i++) {
            gnss_sdr::GnssSynchro ch = stocks.observable(i);
            if (ch.fs() != 0) // Channel is valid.
            {
                channels[ch.channel_id()] = ch;
            } else {
            	std::cerr << "invalid channel" << std::endl;
            }
        }
    }

    void fifo_deser_impl::print_table(std::map<int, gnss_sdr::GnssSynchro>& channels)
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
} /* namespace gr */

