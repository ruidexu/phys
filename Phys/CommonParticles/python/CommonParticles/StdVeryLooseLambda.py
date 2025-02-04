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
# $Id: StdLooseLambda.py,v 1.2 2010-08-24 17:48:00 yamhis Exp $
# =============================================================================
## @file  CommonParticles/StdLooseLambda.py
#  configuration file for 'Standard Loose '
#  @author Patrick Koppenburg
#  @date 2009-02-18
# =============================================================================
"""
Configuration file for 'Standard Very Loose Lambda'
"""
__author__ = "Thomas Blake"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.2 $"
# =============================================================================
__all__ = ('StdVeryLooseLambdaLL', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdVeryLooseLambdaLL = CombineParticles('StdVeryLooseLambdaLL')

StdVeryLooseLambdaLL.Inputs = [
    "Phys/StdAllNoPIDsPions/Particles", "Phys/StdAllNoPIDsProtons/Particles"
]

StdVeryLooseLambdaLL.DecayDescriptor = "[Lambda0 -> p+ pi-]cc"

StdVeryLooseLambdaLL.DaughtersCuts = {
    "pi+": "(P>2*GeV) & (MIPCHI2DV(PRIMARY)>9)",
    "p+": "(P>2*GeV) & (MIPCHI2DV(PRIMARY)>9)"
}

StdVeryLooseLambdaLL.CombinationCut = "(ADAMASS('Lambda0')<50*MeV) & (ADOCACHI2CUT(30, ''))"
StdVeryLooseLambdaLL.MotherCut = "(ADMASS('Lambda0')<35*MeV) & (VFASPF(VCHI2)<30) & (BPVVDCHI2 > 4.)"

## configure Data-On-Demand service
locations = updateDoD(StdVeryLooseLambdaLL)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
