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
"""
Configuration file for Standard Loose DiMuon, very loose for penguins (and other small animals).
"""

__author__ = 'Rob Lambert'
__date__ = '07/07/2009'

from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *
import GaudiKernel.SystemOfUnits as Units

###########################
# StdLooseDiMuon #
###########################

StdVeryLooseDiMuon = CombineParticles("StdVeryLooseDiMuon")
StdVeryLooseDiMuon.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
StdVeryLooseDiMuon.Inputs = ["Phys/StdAllVeryLooseMuons/Particles"]
StdVeryLooseDiMuon.CombinationCut = "(ADAMASS('J/psi(1S)') < 3000.*MeV) & (ADOCACHI2CUT(30, ''))"
StdVeryLooseDiMuon.MotherCut = "(VFASPF(VCHI2) < 25.)"
locations = updateDoD(StdVeryLooseDiMuon)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
