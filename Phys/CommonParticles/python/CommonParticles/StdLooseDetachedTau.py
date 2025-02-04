#!/usr/bin/env python
from __future__ import print_function
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
## @file  CommonParticles/StdLooseDetachedTau.py
#  configuration file for 'Standard Loose Detached Tau'
#  @author Donal Hill, Conor Fitzpatrick, Christian Elsasser
#  @date 2012-12-02
# =============================================================================
__all__ = ('StdLooseDetachedTau3pi', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm - physical tau+ -> pi+ pi- pi+
StdLooseDetachedTau3pi = CombineParticles('StdLooseDetachedTau3pi')

StdLooseDetachedTau3pi.Inputs = ["Phys/StdLoosePions/Particles"]

StdLooseDetachedTau3pi.DecayDescriptors = ["[tau+ -> pi+ pi- pi+]cc"]
StdLooseDetachedTau3pi.DaughtersCuts = {
    "pi+":
    "(PT>150.*MeV) & (MIPCHI2DV(PRIMARY) > 4.0) & (TRCHI2DOF<4) & (TRGHOSTPROB<0.4) & (PIDK < 8)",
    "pi-":
    "(PT>150.*MeV) & (MIPCHI2DV(PRIMARY) > 4.0) & (TRCHI2DOF<4) & (TRGHOSTPROB<0.4) & (PIDK < 8)"
}

StdLooseDetachedTau3pi.CombinationCut = "((AM>400.*MeV) & (AM<3500.*MeV)) & (ADOCAMAX('')<0.15*mm) & ((AM12<1670.*MeV) | (AM23<1670.*MeV)) & (ANUM(PT < 300*MeV) <= 1) & (1<ANUM( ('pi+'==ABSID) & (MIPCHI2DV(PRIMARY)>5)))"
StdLooseDetachedTau3pi.MotherCut = "(M>400.*MeV) & (M < 3500.*MeV) & (BPVDIRA>0.99) & (VFASPF(VCHI2) < 25 )"

## configure Data-On-Demand service
locations = updateDoD(StdLooseDetachedTau3pi)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
