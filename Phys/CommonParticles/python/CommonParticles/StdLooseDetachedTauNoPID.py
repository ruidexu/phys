#!/usr/bin/env python
from __future__ import print_function
###############################################################################
# (c) Copyright 2021 CERN for the benefit of the LHCb Collaboration           #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
## @file  CommonParticles/StdLooseDetachedTauNoPID.py
#  configuration file for 'Standard Loose Detached Tau No PID'
#  @author Donal Hill
#  @date 2021-08-03
# =============================================================================

__all__ = ('StdLooseDetachedTau3piNoPID', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm - physical tau+ -> pi+ pi- pi+
StdLooseDetachedTau3piNoPID = CombineParticles('StdLooseDetachedTau3piNoPID')

StdLooseDetachedTau3piNoPID.Inputs = ["Phys/StdAllNoPIDsPions/Particles"]

StdLooseDetachedTau3piNoPID.DecayDescriptors = ["[tau+ -> pi+ pi- pi+]cc"]
StdLooseDetachedTau3piNoPID.DaughtersCuts = {
    "pi+":
    "(PT>300.*MeV) & (MIPCHI2DV(PRIMARY) > 15) & (TRCHI2DOF<4) & (TRGHOSTPROB<0.4)",
    "pi-":
    "(PT>300.*MeV) & (MIPCHI2DV(PRIMARY) > 15) & (TRCHI2DOF<4) & (TRGHOSTPROB<0.4)"
}

StdLooseDetachedTau3piNoPID.CombinationCut = "(APT>1500.*MeV) & ((AM>400.*MeV) & (AM<3500.*MeV)) & (ADOCAMAX('')<0.15*mm) & ((AM12<1670.*MeV) | (AM23<1670.*MeV))"
StdLooseDetachedTau3piNoPID.MotherCut = "(PT>1500.*MeV) & (M>400.*MeV) & (M < 3500.*MeV) & (BPVVDRHO>0.3*mm) & (BPVDIRA>0.996) & (VFASPF(VCHI2) < 16 )"

## configure Data-On-Demand service
locations = updateDoD(StdLooseDetachedTau3piNoPID)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
