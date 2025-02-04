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
## @file  CommonParticles/StdTightANNDownPions.py
#  configuration file for 'Standard Tight ANN Downstream Pions'
#  @author Chris Jones christopher.rob.jones@cern.ch
#  @date 20/01/2012
# =============================================================================
"""
Configuration file for 'Standard Tight Downstream Pions using ANN PID'
"""
__author__ = "Chris Jones christopher.rob.jones@cern.ch"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.5 $"
# =============================================================================
__all__ = ('StdTightANNDownPions', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombinedParticleMaker
from Configurables import ProtoParticleCALOFilter
from CommonParticles.Utils import *

## create the algorithm
algorithm = CombinedParticleMaker('StdTightANNDownPions', Particle='pion')

# configure the track selector
selector = trackSelector(
    algorithm, trackTypes=['Downstream'], cuts={"Chi2Cut": [0, 10]})

# protoparticle filter:
fltr = protoFilter(algorithm, ProtoParticleCALOFilter, 'Pion')
#fltr.Selection = [ "RequiresDet='RICH' ProbNNpi>'0.2'" ]
fltr.Selection = ["ProbNNpi>'0.07'"]

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdTightANNDownPions = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
