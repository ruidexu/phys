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
# $Id: StandardV0.py,v 1.1 2009-10-09 12:39:26 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StandardV0.py
#  configuration file for 'Standard V0'
#  @author Patrick Koppenburg
#  @date 2009-02-28
# =============================================================================
"""
Configuration file for 'Standard V0'
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.1 $"
# =============================================================================

_locations = {}

from CommonParticles.StdLooseKs import *
_locations.update(locations)

from CommonParticles.StdVeryLooseKs import *
_locations.update(locations)

from CommonParticles.StdLooseLambda import *
_locations.update(locations)

from CommonParticles.StdVeryLooseLambda import *
_locations.update(locations)

from CommonParticles.StdV0FromBrunel import *
_locations.update(locations)

# redefine the locations
locations = _locations

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
