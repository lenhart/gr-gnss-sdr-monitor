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

#ifndef INCLUDED_GNSSSDR_MOD_SIGNAL_GENERATOR_IMPL_H
#define INCLUDED_GNSSSDR_MOD_SIGNAL_GENERATOR_IMPL_H

#include <gnsssdr_mod/signal_generator.h>

namespace gr {
namespace gnsssdr_mod {

class signal_generator_impl : public signal_generator
{
private:
    void message_handler_function(const pmt::pmt_t& msg);
    const std::string portId{ "msg" };


public:
    signal_generator_impl();
    ~signal_generator_impl();

    // Where all the action really happens
    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace gnsssdr_mod
} // namespace gr

#endif /* INCLUDED_GNSSSDR_MOD_SIGNAL_GENERATOR_IMPL_H */
