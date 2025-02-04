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
Phys/ParticleCombiners
----------------------
#]=======================================================================]

gaudi_add_module(ParticleCombiners
    SOURCES
        src/CombineParticles.cpp
        src/NBodyDecays.cpp
    LINK
        Boost::headers
        Gaudi::GaudiKernel
        LHCb::LoKiCoreLib
        Phys::DaVinciInterfacesLib
        Phys::DaVinciKernelLib
        Phys::LoKiArrayFunctorsLib
        Phys::LoKiPhysLib
)
