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
# $Id: StdAllNoPIDsPions.py,v 1.5 2009-07-01 18:42:29 jonrob Exp $
# =============================================================================
## @file  CommonParticles/StdAllNoPIDsPions.py
#  configuration file for 'Standard NoPIDs Pions'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard NoPIDs Pions'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.5 $"
# =============================================================================
__all__ = ('StdAllNoPIDsPions', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import NoPIDsParticleMaker
from CommonParticles.Utils import *

## create the algorithm
algorithm = NoPIDsParticleMaker('StdAllNoPIDsPions', Particle='pion')

# configure the track selector
selector = trackSelector(algorithm)

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdAllNoPIDsPions = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
