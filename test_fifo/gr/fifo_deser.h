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

#ifndef INCLUDED_GNSSSDR_MOD_FIFO_DESER_H
#define INCLUDED_GNSSSDR_MOD_FIFO_DESER_H

#include <gnsssdr_mod/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace gnsssdr_mod {

    /*!
     * \brief <+description of block+>
     * \ingroup gnsssdr_mod
     *
     */
    class GNSSSDR_MOD_API fifo_deser : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<fifo_deser> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of gnsssdr_mod::fifo_deser.
       *
       * To avoid accidental use of raw pointers, gnsssdr_mod::fifo_deser's
       * constructor is in a private implementation
       * class. gnsssdr_mod::fifo_deser::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string fifo);
    };

  } // namespace gnsssdr_mod
} // namespace gr

#endif /* INCLUDED_GNSSSDR_MOD_FIFO_DESER_H */

