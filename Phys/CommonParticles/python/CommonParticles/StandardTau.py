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
# $Id: StandardTau.py,v1.0 2012-08-07 14:44:42 elsasser Exp $
# =============================================================================
## @file  CommonParticles/StandardTau.py
#  configuration file for 'Standard Tau'
#  @author Donal Hill, Conor Fitzpatrick, Christian Elsasser
#  @date 2012-08-07
# =============================================================================
"""
Configuration file for 'Standard Tau'
"""
__author__ = "Donal Hill, Conor Fitzpatrick, Christian Elsasser"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.0 $"
# =============================================================================

_locations = {}

from CommonParticles.StdLooseDetachedTau import *
_locations.update(locations)
from CommonParticles.StdTightDetachedTau import *
_locations.update(locations)
from CommonParticles.StdLooseDetachedTauNoPID import *
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
