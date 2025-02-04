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
# $Id: StdAllNoPIDsVeloPions.py,v 1.0 2016-10-24 15:01:01 decianm Exp $
# =============================================================================
## @file  CommonParticles/StdAllNoPIDsVeloPions.py
#  configuration file for 'Standard NoPIDs Velo Pions'
#  @author Michel De Cian, michel.de.cian@cern.ch
#  @date 2016-10-24
# =============================================================================
"""
Configuration file for 'Standard NoPIDs pions from velo tracks'
"""
__author__ = "Michel De Cian michel.de.cian@cern.ch"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.5 $"
# =============================================================================
__all__ = ('StdAllNoPIDsVeloPions', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import NoPIDsParticleMaker, ChargedProtoParticleMaker
from CommonParticles.Utils import *

## create the algorithm
algorithmPP = ChargedProtoParticleMaker(
    'VeloPP',
    Output="Rec/ProtoP/VeloCharged",
    TrackSelectorType='TrackSelector')

algorithm = NoPIDsParticleMaker(
    'StdAllNoPIDsVeloPions', Particle='pion', Input="Rec/ProtoP/VeloCharged")

# configure the track selector
selectorPP = trackSelector(algorithmPP, trackTypes=["Velo"])
selector = trackSelector(algorithm, trackTypes=["Velo"])

## configure Data-On-Demand service
locations = updateDoD(algorithm)

DataOnDemandSvc().AlgMap.update({
    'Rec/ProtoP/VeloCharged':
    algorithmPP.getFullName()
})

## finally: define the symbol
StdAllNoPIDsVeloPions = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
