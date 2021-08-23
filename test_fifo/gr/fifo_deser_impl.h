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

#ifndef INCLUDED_GNSSSDR_MOD_FIFO_DESER_IMPL_H
#define INCLUDED_GNSSSDR_MOD_FIFO_DESER_IMPL_H

#include <gnsssdr_mod/fifo_deser.h>
#include "gnss_synchro.pb.h"
#include <thread>
#include <fstream>  // std::ifstream

namespace gr {
  namespace gnsssdr_mod {

    class fifo_deser_impl : public fifo_deser
    {
     private:
      // Nothing to declare in this block.

    	std::string file_name;
    	std::ifstream fifo;

    	std::thread d_thread;
    	gr::thread::mutex d_mutex;
    	bool d_finished{ false };
    	void run();

        void populate_monitor_channels(const gnss_sdr::Observables& stocks,
                                       std::map<int, gnss_sdr::GnssSynchro>& channels);
        void print_table(std::map<int, gnss_sdr::GnssSynchro>& channels);

     public:
      fifo_deser_impl(const std::string fifo);
      ~fifo_deser_impl();

      bool start() override;
    };

  } // namespace gnsssdr_mod
} // namespace gr

#endif /* INCLUDED_GNSSSDR_MOD_FIFO_DESER_IMPL_H */

