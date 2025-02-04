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
# $Id: StdLooseJpsi2MuMu.py,v 1.9 2009-06-29 09:16:49 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StdLooseJpsi2MuMu.py
#  configuration file for 'Standard Loose Jpsi2MuMu'
#  @author Greig Cowan
#  @date 2009-06-23
# =============================================================================
"""
Configuration file for 'Standard Loose Jpsi2MuMu'. Lifetime unbiased.
"""
__author__ = "Greig Cowan"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.9 $"
# =============================================================================
__all__ = ('StdLooseJpsi2MuMu', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdLooseJpsi2MuMu = CombineParticles("StdLooseJpsi2MuMu")
StdLooseJpsi2MuMu.Inputs = ["Phys/StdAllLooseMuons/Particles"]
StdLooseJpsi2MuMu.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
StdLooseJpsi2MuMu.CombinationCut = "(ADAMASS('J/psi(1S)') < 100.*MeV) & (ADOCACHI2CUT(30,''))"
StdLooseJpsi2MuMu.MotherCut = "(VFASPF(VCHI2) < 25.)"

## configure Data-On-Demand service
locations = updateDoD(StdLooseJpsi2MuMu)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
