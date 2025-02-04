###############################################################################
from __future__ import print_function
# (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
##!/usr/bin/env python
# =============================================================================
# $Id: StdLooseDetachedPhi.py,v 1.2 2009-07-10 15:19:54 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StdLooseDetachedPhi2KK.py
#  configuration file for 'Standard Loose Detached'
#  @author Greig Cowan
#  @date 2009-06-23
# =============================================================================
"""
Configuration file for 'Standard Loose Detached (i.e., cut on K IP) Phi2KK'
"""
__author__ = "Greig Cowan"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.2 $"
# =============================================================================
__all__ = ('StdLooseDetachedPhi2KK', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdLooseDetachedPhi2KK = CombineParticles("StdLooseDetachedPhi2KK")
StdLooseDetachedPhi2KK.Inputs = ["Phys/StdLooseKaons/Particles"]
StdLooseDetachedPhi2KK.DecayDescriptor = "phi(1020) -> K+ K-"
StdLooseDetachedPhi2KK.DaughtersCuts = {"K+": "(MIPCHI2DV(PRIMARY) > 4.)"}
StdLooseDetachedPhi2KK.CombinationCut = "(AM < 1100.*MeV) & (ADOCACHI2CUT(30,''))"
StdLooseDetachedPhi2KK.MotherCut = "(VFASPF(VCHI2) < 25.0)"

## configure Data-On-Demand service
locations = updateDoD(StdLooseDetachedPhi2KK)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
