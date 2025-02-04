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
# $Id: StandardDiElectron.py,v 1.1 2009-12-09 16:58:47 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StdLoose.py
#  configuration file for 'Standard Loose DiElectron'
#  @author Patrick Koppenburg
#  @date 2009-12-08
# =============================================================================
"""
Configuration file for 'Standard Loose DiElectron'
"""
__author__ = "Rob Lambert"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.1 $"
# =============================================================================
from Gaudi.Configuration import *

## ============================================================================
## create the algorithm

_locations = {}

from CommonParticles.StdLooseDiElectron import *
_locations.update(locations)

from CommonParticles.StdLooseDetachedDiElectron import *
_locations.update(locations)

# redefine the locations
locations = _locations

## configure Data-On-Demand service
#locations = updateDoD ( StdLoose )

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)

    from CommonParticles.Utils import locationsDoD
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
