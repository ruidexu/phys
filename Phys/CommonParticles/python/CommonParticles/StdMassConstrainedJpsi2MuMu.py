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
# $Id: StdMassConstrainedJpsi2MuMu.py,v 1.2 2010-09-05 20:36:44 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StdMassConstrainedJpsi2MuMu.py
#  configuration file for 'Standard mass constrained Jpsi2MuMu'
#  @author Roel Aaij
#  @date 2010-08-31
# =============================================================================
"""
Configuration file for 'Standard mass constrained Jpsi2MuMu'
"""
__author__ = "Roel Aaij"
__version__ = ""
# =============================================================================
__all__ = ('StdMassConstrainedJpsi2MuMu', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
StdMassConstrainedJpsi2MuMu = CombineParticles("StdMassConstrainedJpsi2MuMu")
StdMassConstrainedJpsi2MuMu.Inputs = ["Phys/StdAllLooseMuons/Particles"]
StdMassConstrainedJpsi2MuMu.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
StdMassConstrainedJpsi2MuMu.DaughtersCuts = {
    'mu+': '(PIDmu > 0) & (PT > 0.5*GeV)'
}
StdMassConstrainedJpsi2MuMu.CombinationCut = "(ADAMASS('J/psi(1S)') < 150.*MeV) & (ADOCACHI2CUT(20, ''))"
StdMassConstrainedJpsi2MuMu.MotherCut = "(VFASPF(VCHI2) < 16.) & (MFIT)"

## configure Data-On-Demand service
locations = updateDoD(StdMassConstrainedJpsi2MuMu)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
