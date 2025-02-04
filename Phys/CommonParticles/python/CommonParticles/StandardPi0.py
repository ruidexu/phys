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
# $Id: StandardPi0.py,v 1.1 2009-02-18 15:29:29 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StandardPi0.py
#  configuration file for 'Standard Pi0'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Pi0'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.1 $"
# =============================================================================

_locations = {}

from CommonParticles.StdLooseMergedPi0 import *
_locations.update(locations)

from CommonParticles.StdLooseResolvedPi0 import *
_locations.update(locations)

from CommonParticles.StdLooseDalitzPi0 import *
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
