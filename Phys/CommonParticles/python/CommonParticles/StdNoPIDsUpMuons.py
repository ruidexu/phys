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
# =============================================================================
# =============================================================================
## @file  CommonParticles/StdNoPIDsUpMuons.py
#  configuration file for 'Standard NoPIDs Upstream Muons'
#  @author Vitalii Lisovskyi vitalii.lisovskyi@cern.ch
#  @date 2021-02-23
# =============================================================================
__all__ = ('StdNoPIDsUpMuons', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import NoPIDsParticleMaker

from CommonParticles.Utils import trackSelector, updateDoD

## create the algorithm
algorithm = NoPIDsParticleMaker(
    'StdNoPIDsUpMuons', DecayDescriptor='Muon', Particle='muon')

# configure the track selector
selector = trackSelector(algorithm, trackTypes=['Upstream'])

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdNoPIDsUpMuons = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =================================================================
