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
Phys/JetTagging
---------------
#]=======================================================================]

gaudi_add_header_only_library(JetTaggingLib
    LINK
        Gaudi::GaudiKernel
        LHCb::PhysEvent
        LHCb::RecEvent
)

gaudi_add_module(JetTagging
    SOURCES
        src/FilterJet.cpp
        src/LoKiBDTTag.cpp
        src/LoKiElectronTag.cpp
        src/LoKiIPTag.cpp
        src/LoKiMuonTag.cpp
        src/LoKiSVTag.cpp
        src/LoKiSeedFinderNTrks.cpp
        src/LoKiTopoTag.cpp
        src/LoKiTopoTagDir.cpp
    LINK
        Gaudi::GaudiAlgLib
        Gaudi::GaudiKernel
        JetTaggingLib
        LHCb::DAQEventLib
        LHCb::LoKiCoreLib
        LHCb::MCEvent
        LHCb::PartPropLib
        LHCb::PhysEvent
        LHCb::RecEvent
        Phys::DaVinciInterfacesLib
        Phys::DaVinciKernelLib
        Phys::LoKiPhysLib
        ROOT::MathCore
        ROOT::Physics
        ROOT::TMVA
        
)

gaudi_add_dictionary(JetTaggingDict
    HEADERFILES dict/JetTaggingInterface.h
    SELECTION dict/JetTaggingInterface.xml
    LINK JetTaggingLib
)

gaudi_install(PYTHON)
