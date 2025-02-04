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
# $Id: StandardMuons.py,v 1.2 2009-10-08 12:37:06 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StandardMuons.py
#  configuration file for 'Standard Muons'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Muons'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.2 $"
# =============================================================================

_locations = {}

from CommonParticles.StdAllNoPIDsMuons import *
_locations.update(locations)

from CommonParticles.StdNoPIDsMuons import *
_locations.update(locations)

from CommonParticles.StdAllLooseMuons import *
_locations.update(locations)

from CommonParticles.StdLooseMuons import *
_locations.update(locations)

from CommonParticles.StdAllVeryLooseMuons import *
_locations.update(locations)

from CommonParticles.StdVeryLooseMuons import *
_locations.update(locations)

from CommonParticles.StdTightMuons import *
_locations.update(locations)

from CommonParticles.StdTightANNMuons import *
_locations.update(locations)

from CommonParticles.StdTightANNDownMuons import *
_locations.update(locations)

from CommonParticles.StdNoPIDsUpMuons import *
_locations.update(locations)

from CommonParticles.StdTightANNUpMuons import *
_locations.update(locations)

from CommonParticles.StdLooseDownMuons import *
_locations.update(locations)

from CommonParticles.StdNoPIDsDownMuons import *
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
