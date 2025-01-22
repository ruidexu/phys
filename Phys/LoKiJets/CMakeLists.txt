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
