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
# $Id: StandardKaons.py,v 1.2 2010-06-03 10:31:18 yamhis Exp $
# =============================================================================
## @file  CommonParticles/StandardKaons.py
#  configuration file for 'Standard Kaons'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Kaons'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.2 $"
# =============================================================================

_locations = {}

from CommonParticles.StdAllNoPIDsKaons import *
_locations.update(locations)

from CommonParticles.StdNoPIDsUpKaons import *
_locations.update(locations)

from CommonParticles.StdNoPIDsDownKaons import *
_locations.update(locations)

from CommonParticles.StdNoPIDsKaons import *
_locations.update(locations)

from CommonParticles.StdAllLooseKaons import *
_locations.update(locations)

from CommonParticles.StdAllLooseANNKaons import *
_locations.update(locations)

from CommonParticles.StdLooseKaons import *
_locations.update(locations)

from CommonParticles.StdLooseANNKaons import *
_locations.update(locations)

from CommonParticles.StdLooseDownKaons import *
_locations.update(locations)

from CommonParticles.StdTightKaons import *
_locations.update(locations)

from CommonParticles.StdTightANNKaons import *
_locations.update(locations)

from CommonParticles.StdLooseANNDownKaons import *
_locations.update(locations)

from CommonParticles.StdTightANNDownKaons import *
_locations.update(locations)

from CommonParticles.StdLooseANNUpKaons import *
_locations.update(locations)

from CommonParticles.StdTightANNUpKaons import *
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
