/* -*- c++ -*- */

#define GNSSSDR_MOD_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "gnsssdr_mod_swig_doc.i"

%{
#include "gnsssdr_mod/de_serializer.h"
#include "gnsssdr_mod/signal_generator.h"
%}

%include "gnsssdr_mod/de_serializer.h"
GR_SWIG_BLOCK_MAGIC2(gnsssdr_mod, de_serializer);
%include "gnsssdr_mod/signal_generator.h"
GR_SWIG_BLOCK_MAGIC2(gnsssdr_mod, signal_generator);

