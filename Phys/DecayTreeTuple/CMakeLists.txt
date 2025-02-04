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
Phys/DecayTreeTuple
-------------------
#]=======================================================================]

gaudi_add_module(DecayTreeTuple
    SOURCES
        src/TupleToolAllTracks.cpp
        src/TupleToolAngles.cpp
        src/TupleToolBeamSpot.cpp
        src/TupleToolBremInfo.cpp
        src/TupleToolBs2MuMuIso2.cpp
        src/TupleToolCaloDigits.cpp
        src/TupleToolCaloHypo.cpp
        src/TupleToolCentrality.cpp
        src/TupleToolCorrectedMass.cpp
        src/TupleToolDOCA.cpp
        src/TupleToolDecayTreeFitter.cpp
        src/TupleToolDira.cpp
        src/TupleToolGeometry.cpp
        src/TupleToolHOP.cpp
        src/TupleToolIsoGeneric.cpp
        src/TupleToolIsolationTwoBody.cpp
        src/TupleToolKinematic.cpp
        src/TupleToolMassHypo.cpp
	    src/TupleToolMultiplicity.cpp
        src/TupleToolNeutrinoReco.cpp
        src/TupleToolP2VV.cpp
        src/TupleToolParticleReFit.cpp
        src/TupleToolParticleStats.cpp
        src/TupleToolPhotonInfo.cpp
        src/TupleToolPi0Info.cpp
        src/TupleToolPid.cpp
        src/TupleToolPropertime.cpp
        src/TupleToolRadUpDownAsym.cpp
        src/TupleToolSelResults.cpp
        src/TupleToolSubMass.cpp
        src/TupleToolTagging.cpp
        src/TupleToolTwoParticleMatching.cpp
        src/TupleToolVeto.cpp
        src/TupleToolVtxDaughters.cpp
        src/TupleToolVtxIsoln.cpp
    LINK
        Analysis::DecayTreeTupleBaseLib
        Boost::headers
        Gaudi::GaudiAlgLib
        Gaudi::GaudiKernel
        GSL::gsl
        LHCb::CaloDAQLib
        LHCb::CaloDetLib
        LHCb::CaloInterfacesLib
        LHCb::CaloUtils
        LHCb::DAQEventLib
        LHCb::DigiEventLib
        LHCb::GenEvent
        LHCb::HltDAQLib
        LHCb::HltEvent
        LHCb::LHCbKernel
        LHCb::LoKiCoreLib
        LHCb::MCAssociatorsLib
        LHCb::MCEvent
        LHCb::MuonDetLib
        LHCb::PartPropLib
        LHCb::PhysEvent
        LHCb::RecEvent
        LHCb::RelationsLib
        LHCb::TrackEvent
        Phys::DaVinciInterfacesLib
        Phys::DaVinciKernelLib
        Phys::DaVinciMCKernelLib
        Phys::DaVinciTypesLib
        Phys::DecayTreeFitter
        Phys::LoKiArrayFunctorsLib
        Phys::LoKiLib
        Phys::LoKiPhysLib
        Phys::LoKiUtils
        Phys::TeslaToolsLib
        Rec::RecInterfacesLib
        Rec::TrackInterfacesLib
        ROOT::GenVector
        ROOT::MathCore
        ROOT::Matrix
        ROOT::Physics
        ROOT::TMVA
)

gaudi_install(PYTHON)

gaudi_add_tests(QMTest)
