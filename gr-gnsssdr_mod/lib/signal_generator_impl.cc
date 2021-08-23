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

#include "signal_generator_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace gnsssdr_mod {

signal_generator::sptr signal_generator::make()
{
    return gnuradio::get_initial_sptr(new signal_generator_impl());
}

void signal_generator_impl::message_handler_function(const pmt::pmt_t& msg)
{
    pmt::print(msg);
}


/*
 * The private constructor
 */
signal_generator_impl::signal_generator_impl()
    : gr::block("signal_generator",
                gr::io_signature::make(0, 0, sizeof(0)),
                gr::io_signature::make(1, 1, sizeof(uint16_t)))
{
    message_port_register_in(pmt::mp(portId));
    set_msg_handler(pmt::intern(portId),
                    [this](const pmt::pmt_t& msg) { message_handler_function(msg); });
}

/*
 * Our virtual destructor.
 */
signal_generator_impl::~signal_generator_impl() {}

int signal_generator_impl::general_work(int noutput_items,
                                        gr_vector_int& ninput_items,
                                        gr_vector_const_void_star& input_items,
                                        gr_vector_void_star& output_items)
{


    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.
    return 0;
}

} /* namespace gnsssdr_mod */
} /* namespace gr */
