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
## @file  CommonParticles/StdLooseProtons.py
#  configuration file for 'Standard Loose Protons'
#  @author Patrick Koppenburg
#  @date 2011-07-18
# =============================================================================
"""
Configuration file for 'Standard Loose Protons with loose cuts'
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.4 $"
# =============================================================================
__all__ = ('StdLooseProtons', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import FilterDesktop
from CommonParticles.Utils import *

## create the algorithm
algorithm = FilterDesktop(
    'StdLooseProtons',
    Inputs=["Phys/StdAllLooseProtons/Particles"],
    Code=defaultCuts())

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdLooseProtons = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
