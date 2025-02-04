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
# $Id: StdLooseDownKaons.py
# =============================================================================
## @file  CommonParticles/StdLooseDownKaons.py
#  configuration file for 'Standard  Loose Down Kaons'
#  @author Yasmine Amhis
#  @date 2010-06-03
# =============================================================================
"""
Configuration file for 'Standard Loose Downstream Kaons'
"""
__author__ = "Yasmine Amhis <yasmine.amhis@epfl.ch> "
__version__ = ""
# =============================================================================
__all__ = ('StdLooseDownKaons', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import ProtoParticleCALOFilter, CombinedParticleMaker

from CommonParticles.Utils import *

## create the algorithm
algorithm = CombinedParticleMaker('StdLooseDownKaons', Particle='kaon')

# configure the track selector
selector = trackSelector(algorithm, trackTypes=['Downstream'])

# protoparticle filter:
fltr = protoFilter(algorithm, ProtoParticleCALOFilter, 'Kaon')
fltr.Selection = ["RequiresDet='RICH' CombDLL(k-pi)>'-5.0'"]

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdLooseDownKaons = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
