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

#ifndef INCLUDED_GNSSSDR_MOD_DE_SERIALIZER_IMPL_H
#define INCLUDED_GNSSSDR_MOD_DE_SERIALIZER_IMPL_H

#include <gnsssdr_mod/de_serializer.h>

#include "gnss_synchro_udp_source.h"

namespace gr {
namespace gnsssdr_mod {

class de_serializer_impl : public de_serializer
{
private:
    const uint16_t b_port;

    std::shared_ptr<Gnss_Synchro_Udp_Source> gnss_sync_src_sptr;

    void populate_channels(const gnss_sdr::Observables& stocks,
                           std::map<int, gnss_sdr::GnssSynchro>& channels);
    void print_table(gnss_sdr::Observables& stocks);

public:
    de_serializer_impl(uint16_t port);
    ~de_serializer_impl();

    bool start() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace gnsssdr_mod
} // namespace gr

#endif /* INCLUDED_GNSSSDR_MOD_DE_SERIALIZER_IMPL_H */
