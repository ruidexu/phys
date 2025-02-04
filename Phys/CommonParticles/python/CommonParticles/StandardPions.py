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
# $Id: StandardPions.py,v 1.3 2009-10-08 12:37:06 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StandardPions.py
#  configuration file for 'Standard Pions'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Pions'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.3 $"
# =============================================================================

_locations = {}

from CommonParticles.StdAllNoPIDsPions import *
_locations.update(locations)

from CommonParticles.StdNoPIDsPions import *
_locations.update(locations)

from CommonParticles.StdNoPIDsDownPions import *
_locations.update(locations)

from CommonParticles.StdNoPIDsUpPions import *
_locations.update(locations)

from CommonParticles.StdAllLoosePions import *
_locations.update(locations)

from CommonParticles.StdLoosePions import *
_locations.update(locations)

from CommonParticles.StdTightPions import *
_locations.update(locations)

from CommonParticles.StdAllLooseANNPions import *
_locations.update(locations)

from CommonParticles.StdLooseANNPions import *
_locations.update(locations)

from CommonParticles.StdTightANNPions import *
_locations.update(locations)

from CommonParticles.StdLooseANNDownPions import *
_locations.update(locations)

from CommonParticles.StdTightANNDownPions import *
_locations.update(locations)

from CommonParticles.StdLooseANNUpPions import *
_locations.update(locations)

from CommonParticles.StdTightANNUpPions import *
_locations.update(locations)

from CommonParticles.StdAllNoPIDsVeloPions import *
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
