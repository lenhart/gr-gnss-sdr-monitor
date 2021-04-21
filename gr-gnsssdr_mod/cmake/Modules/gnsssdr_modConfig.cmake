INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_GNSSSDR_MOD gnsssdr_mod)

FIND_PATH(
    GNSSSDR_MOD_INCLUDE_DIRS
    NAMES gnsssdr_mod/api.h
    HINTS $ENV{GNSSSDR_MOD_DIR}/include
        ${PC_GNSSSDR_MOD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GNSSSDR_MOD_LIBRARIES
    NAMES gnuradio-gnsssdr_mod
    HINTS $ENV{GNSSSDR_MOD_DIR}/lib
        ${PC_GNSSSDR_MOD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnsssdr_modTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GNSSSDR_MOD DEFAULT_MSG GNSSSDR_MOD_LIBRARIES GNSSSDR_MOD_INCLUDE_DIRS)
MARK_AS_ADVANCED(GNSSSDR_MOD_LIBRARIES GNSSSDR_MOD_INCLUDE_DIRS)
