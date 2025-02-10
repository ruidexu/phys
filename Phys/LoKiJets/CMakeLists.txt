###############################################################################
# (c) Copyright 2000-2021 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
#[=======================================================================[.rst:
Phys/LoKiJets
-------------
#]=======================================================================]

find_path(FJCONTRIB_INCLUDE_DIR fastjet/contrib/ConstituentSubtractor.hh
          HINTS $ENV{FJCONTRIB_ROOT_DIR}/include ${FJCONTRIB_ROOT_DIR}/include)

find_library(FJCONTRIB_LIBRARY NAMES fastjetcontribfragile
             HINTS $ENV{FJCONTRIB_ROOT_DIR}/lib ${FJCONTRIB_ROOT_DIR}/lib)

find_library(FJCONTRIB_CS_LIBRARY NAMES ConstituentSubtractor
             HINTS $ENV{FJCONTRIB_ROOT_DIR}/lib ${FJCONTRIB_ROOT_DIR}/lib)

# handle the QUIETLY and REQUIRED arguments and set FJCONTRIB_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(fjcontrib DEFAULT_MSG FJCONTRIB_INCLUDE_DIR FJCONTRIB_LIBRARY FJCONTRIB_CS_LIBRARY)

mark_as_advanced(FJCONTRIB_FOUND FJCONTRIB_INCLUDE_DIR FJCONTRIB_LIBRARY FJCONTRIB_CS_LIBRARY)

set(FJCONTRIB_INCLUDE_DIRS ${FJCONTRIB_INCLUDE_DIR})
set(FJCONTRIB_LIBRARIES ${FJCONTRIB_LIBRARY})
get_filename_component(FJCONTRIB_LIBRARY_DIRS ${FJCONTRIB_LIBRARY} PATH)

if(NOT TARGET fjcontrib::fjcontrib)
  if(FJCONTRIB_FOUND)
    add_library(fjcontrib::fjcontrib IMPORTED INTERFACE)
    target_include_directories(fjcontrib::fjcontrib SYSTEM INTERFACE ${FJCONTRIB_INCLUDE_DIR})
    target_link_libraries(fjcontrib::fjcontrib INTERFACE ${FJCONTRIB_LIBRARY} FastJet::FastJet)
    add_library(fjcontrib::ConstituentSubtractor IMPORTED INTERFACE)
    target_include_directories(fjcontrib::ConstituentSubtractor SYSTEM INTERFACE ${FJCONTRIB_INCLUDE_DIR})
    target_link_libraries(fjcontrib::ConstituentSubtractor INTERFACE ${FJCONTRIB_CS_LIBRARY} FastJet::FastJet)
  endif()
endif()

# Find fastjet/tools/GridMedianBackgroundEstimator
find_path(FASTJET_INCLUDE_DIR fastjet/tools/GridMedianBackgroundEstimator.hh
          HINTS $ENV{FASTJET_ROOT_DIR}/include ${FASTJET_ROOT_DIR}/include)

find_library(FASTJET_LIBRARY NAMES fastjet
             HINTS $ENV{FASTJET_ROOT_DIR}/lib ${FASTJET_ROOT_DIR}/lib)

find_library(FASTJET_TOOLS_LIBRARY NAMES fastjettools
             HINTS $ENV{FASTJET_ROOT_DIR}/lib ${FASTJET_ROOT_DIR}/lib)

# Check if required components are found
if(NOT FASTJET_INCLUDE_DIR OR NOT FASTJET_LIBRARY OR NOT FASTJET_TOOLS_LIBRARY)
    message(FATAL_ERROR "FastJet or its tools library not found!")
endif()

# Include directories and link libraries
#include_directories(${FASTJET_INCLUDE_DIR})
#set(FASTJET_LIBRARIES ${FASTJET_LIBRARY} ${FASTJET_TOOLS_LIBRARY})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(tools DEFAULT_MSG FASTJET_INCLUDE_DIR FASTJET_LIBRARY FASTJET_TOOLS_LIBRARY)

mark_as_advanced(FASTJET_INCLUDE_DIR FASTJET_LIBRARY FASTJET_TOOLS_LIBRARY)

set(FASTJET_INCLUDE_DIRS ${FASTJET_INCLUDE_DIR})
set(FASTJET_LIBRARIES ${FASTJET_LIBRARY})
get_filename_component(FASTJET_TOOLS_LIBRARIES ${FASTJET_TOOLS_LIBRARY} PATH)

if(NOT TARGET tools::tools)
  if(FJCONTRIB_FOUND)
    add_library(tools::tools IMPORTED INTERFACE)
    target_include_directories(tools::tools SYSTEM INTERFACE ${FASTJET_INCLUDE_DIR})
    target_link_libraries(tools::tools INTERFACE ${FASTJET_LIBRARY} FastJet::FastJet)
    add_library(tools::GridMedianBackgroundEstimator IMPORTED INTERFACE)
    target_include_directories(tools::GridMedianBackgroundEstimator SYSTEM INTERFACE ${FASTJET_INCLUDE_DIR})
    target_link_libraries(tools::GridMedianBackgroundEstimator INTERFACE ${FASTJET_TOOLS_LIBRARY} FastJet::FastJet)
  endif()
endif()


gaudi_add_module(LoKiJets
    SOURCES
        src/LoKiFastJetMaker.cpp
        src/LoKiFastJetWithAreaMaker.cpp
        src/LoKiJetMakerAlg.cpp
        src/LoKiJetMakerWR2VtxAlg.cpp
        src/LoKiJetParticleMaker.cpp
        src/LoKiJets2JetsAlg.cpp
        src/LoKiSeedConeJetMaker.cpp
        src/LoKiSeedFinder.cpp
        src/LoKiVVSeedFinder.cpp
        src/LoKiConstituentSub.cpp
    LINK
        AIDA::aida
        Boost::headers
        FastJet::FastJet
        tools::tools
        tools::GridMedianBackgroundEstimator
        fjcontrib::fjcontrib
        fjcontrib::ConstituentSubtractor
        Gaudi::GaudiAlgLib
        Gaudi::GaudiKernel
        Gaudi::GaudiUtilsLib
        LHCb::LHCbMathLib
        LHCb::LoKiCoreLib
        LHCb::PhysEvent
        LHCb::RecEvent
        Phys::DaVinciInterfacesLib
        Phys::DaVinciKernelLib
        Phys::DaVinciTypesLib
        Phys::LoKiAlgo
        Phys::LoKiPhysLib
        ROOT::GenVector
        ROOT::Hist
        ROOT::MathCore
)

find_path(FASTJET_INCLUDE_DIR fastjet/tools/GridMedianBackgroundEstimator.hh
          HINTS $ENV{FASTJET_ROOT_DIR}/include ${FASTJET_ROOT_DIR}/include)

find_library(FASTJET_LIBRARY NAMES fastjet
             HINTS $ENV{FASTJET_ROOT_DIR}/lib ${FASTJET_ROOT_DIR}/lib)

if(NOT FASTJET_INCLUDE_DIR OR NOT FASTJET_LIBRARY)
    message(FATAL_ERROR "FastJet library or include directory not found.")
endif()

gaudi_install(PYTHON)
