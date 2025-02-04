#!/usr/bin/env python
from __future__ import print_function
###############################################################################
# (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
"""
Configuration file for 'Standard Tight Phi2KK'. Lieftime unbiased.
"""
__author__ = "Jibo He"
__date__ = "3/2/2012"

# =============================================================================
__all__ = ('StdTightPhi2KK', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdTightPhi2KK = CombineParticles("StdTightPhi2KK")
StdTightPhi2KK.Inputs = ["Phys/StdTightKaons/Particles"]
StdTightPhi2KK.DecayDescriptor = "phi(1020) -> K+ K-"
StdTightPhi2KK.DaughtersCuts = {"K+": "(PT>500*MeV)"}
StdTightPhi2KK.CombinationCut = "(ADAMASS('phi(1020)')<30*MeV) & (ADOCACHI2CUT(30, ''))"
StdTightPhi2KK.MotherCut = "(VFASPF(VCHI2) < 25.0)"

## configure Data-On-Demand service
locations = updateDoD(StdTightPhi2KK)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
