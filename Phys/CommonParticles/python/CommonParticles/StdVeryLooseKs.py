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
Configuration file for 'Standard Very Loose Ks'
These Very Loose Ks candidates do not have a cut on the pT of the pion
by loading NoPIDsPions instead of LoosePions.
This increases the yield of LL Ks's by about 20 to 30%.
"""
__author__ = "Mick Mulder"
# =============================================================================
__all__ = ('StdVeryLooseKsLL', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles, FilterDesktop
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdVeryLooseKsLL = CombineParticles('StdVeryLooseKsLL')

StdVeryLooseKsLL.Inputs = ["Phys/StdAllNoPIDsPions/Particles"]
StdVeryLooseKsLL.DecayDescriptor = "KS0 -> pi+ pi-"

StdVeryLooseKsLL.DaughtersCuts = {
    "pi+": "(P > 2.*GeV) & (MIPCHI2DV(PRIMARY) > 9.)"
}
StdVeryLooseKsLL.CombinationCut = "(ADAMASS('KS0') < 50.*MeV) & (ADOCACHI2CUT(30, '')) "
StdVeryLooseKsLL.MotherCut = "(ADMASS('KS0') < 35.*MeV) & (CHI2VX < 30.) & (BPVVDCHI2>4.)"

## configure Data-On-Demand service
locations = updateDoD(StdVeryLooseKsLL)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
