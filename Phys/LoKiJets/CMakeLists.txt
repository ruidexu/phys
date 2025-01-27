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
        src/LoKiConstituentSubtractor.cpp
    LINK
        AIDA::aida
        Boost::headers
        FastJet::FastJet
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

gaudi_install(PYTHON)
