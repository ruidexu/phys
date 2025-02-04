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
# $Id: StandardJpsi.py,v 1.4 2010-09-01 14:16:42 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StandardJpsi.py
#  configuration file for 'Standard Jpsi'
#  @author Patrick Koppenburg
#  @date 2009-02-28
# =============================================================================
"""
Configuration file for 'Standard Jpsi'
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.4 $"
# =============================================================================

_locations = {}

from CommonParticles.StdLooseJpsi2MuMu import *
_locations.update(locations)

from CommonParticles.StdVeryLooseJpsi2MuMu import *
_locations.update(locations)

from CommonParticles.StdLooseJpsi2ee import *
_locations.update(locations)

from CommonParticles.StdLTUnbiasedJpsi2MuMu import *
_locations.update(locations)

from CommonParticles.StdMassConstrainedJpsi2MuMu import *
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
