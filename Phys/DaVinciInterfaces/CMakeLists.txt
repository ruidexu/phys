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
Phys/DaVinciInterfaces
----------------------
#]=======================================================================]

gaudi_add_library(DaVinciInterfacesLib
    SOURCES
        src/DaVinciInterfaces.cpp
        src/GetIDVAlgorithm.cpp
    LINK
        PUBLIC
            Gaudi::GaudiKernel
            LHCb::CaloUtils
            LHCb::LHCbKernel
            LHCb::PhysEvent
            LHCb::RecEvent
            LHCb::RelationsLib
            Phys::DaVinciTypesLib 
            FastJet::FastJet       
        PRIVATE
            Gaudi::GaudiAlgLib
)

gaudi_add_dictionary(DaVinciInterfacesDict
    HEADERFILES dict/DaVinciInterfacesDict.h
    SELECTION dict/DaVinciInterfacesDict.xml
    LINK DaVinciInterfacesLib
)
