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
Configuration file for Standard All Loose Pi-Mu+ pair, potentially detached.
"""

__author__ = 'Benoit VIAUD'
__date__ = '13/05/2015'

from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *
import GaudiKernel.SystemOfUnits as Units

##############################
# StdAllLooseMuPion #
##############################
StdAllLooseMuPion = CombineParticles("StdAllLooseMuPion")
StdAllLooseMuPion.DecayDescriptor = "rho(770)0  -> mu+ pi-"
StdAllLooseMuPion.Inputs = [
    "Phys/StdAllLooseMuons/Particles", "Phys/StdAllLoosePions/Particles"
]
StdAllLooseMuPion.DaughtersCuts = {
    "mu+": "(PT>200*MeV) & (MIPCHI2DV(PRIMARY)>0.)",
    "pi-": "(PT>200*MeV) & (MIPCHI2DV(PRIMARY)>0.)"
}
StdAllLooseMuPion.CombinationCut = "(ADOCACHI2CUT(30,''))"
StdAllLooseMuPion.MotherCut = "(VFASPF(VCHI2)<25)"
locations = updateDoD(StdAllLooseMuPion)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
