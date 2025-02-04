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
Phys/DecayTreeTupleJets
-----------------------
#]=======================================================================]

gaudi_add_module(DecayTreeTupleJets
    SOURCES
        src/TupleToolJetRelations.cpp
        src/TupleToolJetTag.cpp
        src/TupleToolJets.cpp
        src/TupleToolJetsBase.cpp
        src/TupleToolJetsForB.cpp
        src/TupleToolWZJets.cpp
    LINK
        Analysis::DecayTreeTupleBaseLib
        Boost::headers
        Gaudi::GaudiAlgLib
        LHCb::HltEvent
        LHCb::PartPropLib
        LHCb::PhysEvent
        Phys::DaVinciInterfacesLib
        Phys::DaVinciKernelLib
        Phys::JetAccessoriesLib
        Phys::JetTaggingLib
        Phys::LoKiArrayFunctorsLib
        Phys::LoKiLib
        Phys::LoKiPhysLib
)
