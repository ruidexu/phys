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
# $Id: StdVeryLooseJpsi2MuMu.py,v 1.1 2010-01-18 10:08:49 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StdVeryLooseJpsi2MuMu.py
#  configuration file for 'Standard Very Loose Jpsi2MuMu'
#  @author Greig Cowan
#  @date 2009-06-23
# =============================================================================
"""
Configuration file for 'Standard Very Loose Jpsi2MuMu'
"""
__author__ = "Greig Cowan"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.1 $"
# =============================================================================
__all__ = ('StdVeryLooseJpsi2MuMu', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdVeryLooseJpsi2MuMu = CombineParticles("StdVeryLooseJpsi2MuMu")
StdVeryLooseJpsi2MuMu.Inputs = ["Phys/StdVeryLooseMuons/Particles"]
StdVeryLooseJpsi2MuMu.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
StdVeryLooseJpsi2MuMu.CombinationCut = "(ADAMASS('J/psi(1S)') < 100.*MeV) & (ADOCACHI2CUT(30, ''))"
StdVeryLooseJpsi2MuMu.MotherCut = "(VFASPF(VCHI2) < 25.)"

## configure Data-On-Demand service
locations = updateDoD(StdVeryLooseJpsi2MuMu)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
