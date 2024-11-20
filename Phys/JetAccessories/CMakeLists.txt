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
Phys/JetAccessories
-------------------
#]=======================================================================]

gaudi_add_header_only_library(JetAccessoriesLib
    LINK
        Gaudi::GaudiKernel
        LHCb::CaloDetLib
        LHCb::PartPropLib
        LHCb::PhysEvent
        LHCb::RecEvent
        Phys::DaVinciInterfacesLib
)

gaudi_add_module(JetAccessories
    SOURCES
        src/ClearDaughters.cpp
        src/HighPtIsoLeptonAndTagPV.cpp
        src/HltJetBuilder.cpp
        src/HltParticleFlow.cpp
        src/PFJetMakerAlg.cpp
        src/PFParticle.cpp
        src/PFlowProtoFilter.cpp
        src/ParticleFlow.cpp
        src/ParticleFlow4Jets.cpp
        src/SplitJets.cpp
        src/UpdateJetsWithVtx.cpp
        src/VBVertexRequirement.cpp
    LINK
        AIDA::aida
        Boost::headers
        Gaudi::GaudiAlgLib
        Gaudi::GaudiKernel
        Gaudi::GaudiUtilsLib
        JetAccessoriesLib
        LHCb::CaloDetLib
        LHCb::CaloUtils
        LHCb::DAQEventLib
        LHCb::DigiEventLib
        LHCb::LHCbKernel
        LHCb::LHCbMathLib
        LHCb::LoKiCoreLib
        LHCb::MuonDAQLib
        LHCb::PartPropLib
        LHCb::PhysEvent
        LHCb::RecEvent
        LHCb::RelationsLib
        LHCb::TrackEvent
        Phys::DaVinciInterfacesLib
        Phys::DaVinciKernelLib
        Phys::DaVinciTypesLib
        Phys::KalmanFilter
        Phys::LoKiAlgo
        Phys::LoKiPhysLib
        Rec::LoKiTrackLib
        Rec::TrackInterfacesLib
        Rec::TrackKernel
        ROOT::GenVector
        ROOT::Hist
        ROOT::MathCore        
)

gaudi_install(PYTHON)

gaudi_add_dictionary(JetAccessoriesDict
    HEADERFILES dict/JetAccessoriesDict.h
    SELECTION dict/JetAccessories.xml
    LINK JetAccessoriesLib
)
