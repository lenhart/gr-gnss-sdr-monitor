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

de_serializer::sptr de_serializer::make(uint16_t port)
{
    return gnuradio::get_initial_sptr(new de_serializer_impl(port));
}


/*
 * The private constructor
 */
de_serializer_impl::de_serializer_impl(uint16_t port)
    : gr::sync_block(
          "de_serializer",
          gr::io_signature::make(0, 0, 0),
          gr::io_signature::make(
              1, 1, sizeof(gr_complex))), // dummy output. will convert to sth meaningful
      b_port(port)
{
}

/*
 * Our virtual destructor.
 */
de_serializer_impl::~de_serializer_impl() {}

bool de_serializer_impl::start()
{
    gnss_sync_src_sptr = std::make_shared<Gnss_Synchro_Udp_Source>(b_port);
    std::cout << std::setw(3) << "CH" << std::setw(6) << "PRN" << std::setw(14)
              << "CN0 [dB-Hz]" << std::setw(17) << "Doppler [Hz]\n"
              << '\n';
    return true;
}

int de_serializer_impl::work(int noutput_items,
                             gr_vector_const_void_star& input_items,
                             gr_vector_void_star& output_items)
{
    gr_complex* out = (gr_complex*)output_items[0];
    gnss_sdr::Observables stocks;
    bool success = gnss_sync_src_sptr->read_gnss_synchro(stocks);
    if (success) {
        print_table(stocks); // TODO REPLACE BY ACTUAL PASSING OUT TO NEXT BLOCK
        // populate_channels(stocks);
        // print_table(stocks, )
    }
    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.

    // we return varying number of data -> call produce & return flag
    produce(0, 0);
    return this->WORK_CALLED_PRODUCE;
}

void de_serializer_impl::populate_channels(const gnss_sdr::Observables& stocks,
                                           std::map<int, gnss_sdr::GnssSynchro>& channels)
{

    for (std::size_t i = 0; i < stocks.observable_size(); i++) {
        gnss_sdr::GnssSynchro ch = stocks.observable(i);
        if (ch.fs() != 0) // Channel is valid.
        {
            channels[ch.channel_id()] = ch;
        }
    }
}

void de_serializer_impl::print_table(gnss_sdr::Observables& stocks)
{
    std::map<int, gnss_sdr::GnssSynchro> channels;
    populate_channels(stocks, channels);

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
