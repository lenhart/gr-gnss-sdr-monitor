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

#include <gnsssdr_mod/de_serializer.h> // TODO WHY DOES GNU RADIO INCLUDE IT LIKE THIS? THIS CONFUSES CLANG-FORMAT

#include "gnss_pvt_udp_source.h"
#include "gnss_synchro.pb.h"
#include "gnss_synchro_udp_source.h"
#include "monitor_pvt.pb.h"

namespace gr {
namespace gnsssdr_mod {


/**
 * 1st attempt, does everything in one block, incl. reading both streams
 */
class de_serializer_impl : public de_serializer
{
private:
    const uint16_t b_port_monitor;
    const uint16_t b_port_pvt;

    std::shared_ptr<Gnss_Synchro_Udp_Source> gnss_sync_src_sptr;
    std::shared_ptr<Gnss_Pvt_Udp_Source> gnss_pvt_src_sptr;

    void process(const gnss_sdr::Observables& stocks, float* out);

    void populate_monitor_channels(const gnss_sdr::Observables& stocks,
                                   std::map<int, gnss_sdr::GnssSynchro>& channels);
    void print_table(std::map<int, gnss_sdr::GnssSynchro>& channels);

    void test_msg_passing(); // to test message passing to next block

    std::thread d_thread;
    gr::thread::mutex d_mutex;
    bool d_finished{ false };
    void run();

public:
    de_serializer_impl(uint16_t port_monitor, uint16_t port_pvt);
    ~de_serializer_impl();

    bool start() override;
};

} // namespace gnsssdr_mod
} // namespace gr

#endif /* INCLUDED_GNSSSDR_MOD_DE_SERIALIZER_IMPL_H */
