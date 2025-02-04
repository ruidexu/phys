#!/usr/bin/env python
from __future__ import print_function
###############################################################################
# (c) Copyright 2000-2022 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
# =============================================================================
# $Id: StdNoPIDsDownMuons.py, v 0.1 2022-03-03 18:42:29 fredi $
# =============================================================================
## @file  CommonParticles/StdNoPIDsDownMuons.py
#  configuration file for 'Standard NoPIDs Downstream Muons'
#  @author Federico Leo Redi Federico.Redi@cern.ch
#  @date 2022-03-03
# =============================================================================
"""
Configuration file for 'Standard NoPIDs Downstream Muons'
"""
__author__ = "Federico Leo Redi <Federico.Redi@cern.ch>"
__version__ = "Version $Revision: 0.1 $"
# =============================================================================
__all__ = ('StdNoPIDsDownMuons', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import NoPIDsParticleMaker

from CommonParticles.Utils import *

## create the algorithm
algorithm = NoPIDsParticleMaker(
    'StdNoPIDsDownMuons', DecayDescriptor='Muon', Particle='muon')

# configure the track selector
selector = trackSelector(
    algorithm, trackTypes=['Downstream'], cuts={"Chi2Cut": [0, 10]})

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdNoPIDsDownMuons = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
