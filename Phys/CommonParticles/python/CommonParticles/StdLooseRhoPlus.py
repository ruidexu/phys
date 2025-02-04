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
# =============================================================================
# $Id: StdLooseRhoPlus.py,v 1.3 2009-04-22 14:17:39 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StdLooseRhoPlus.py
#  configuration file for 'Standard Loose RhoPlus'
#  @author Patrick Koppenburg
#  @date 2009-02-18
# =============================================================================
"""
Configuration file for 'Standard Loose RhoPlus'
"""
__author__ = "Yasmine Amhis"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.3 $"
# =============================================================================
__all__ = ('StdLooseRhoPlus', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdLooseRhoPlus = CombineParticles('StdLooseRhoPlus')

StdLooseRhoPlus = CombineParticles("StdLooseRhoPlus")
StdLooseRhoPlus.Inputs = [
    "Phys/StdLooseMergedPi0/Particles", "Phys/StdLooseResolvedPi0/Particles",
    "Phys/StdLoosePions/Particles", "Phys/StdLooseKaons/Particles"
]
StdLooseRhoPlus.DecayDescriptor = "[rho(770)- -> pi- pi0]cc"
StdLooseRhoPlus.DaughtersCuts = {
    "pi+": "ALL",
    "K+": "ALL",
    "pi0": "(PT>1000*MeV)  & (P> 1500*MeV)"
}
#Note
#The cut of 550 MeV around the K*(892)+ is NOT a typo, is motivated
#by the requirements of the B2DVec HLT2 selection
StdLooseRhoPlus.CombinationCut = "(ADAMASS('K*(892)+')<550*MeV)"
StdLooseRhoPlus.MotherCut = "ALL"

## configure Data-On-Demand service
locations = updateDoD(StdLooseRhoPlus)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
