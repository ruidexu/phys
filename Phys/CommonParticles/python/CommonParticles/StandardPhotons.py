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
# $Id: StandardPhotons.py,v 1.1 2009-01-15 14:22:14 ibelyaev Exp $
# =============================================================================
## @file  CommonParticles/StandardPhotons.py
#  configuration file for 'Standard Photons'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Photons'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.1 $"
# =============================================================================

_locations = {}

from CommonParticles.StdLoosePhotons import *
_locations.update(locations)

from CommonParticles.StdLooseCnvPhotons import *
_locations.update(locations)

from CommonParticles.StdLooseAllPhotons import *
_locations.update(locations)

from CommonParticles.StdVeryLooseAllPhotons import *
_locations.update(locations)

from CommonParticles.StdAllLooseGammaConversion import *
_locations.update(locations)

from CommonParticles.StdAllTightGammaConversion import *
_locations.update(locations)

from CommonParticles.StdAllTightSymGammaConversion import *
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
