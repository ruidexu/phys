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
# $Id: StandardIntermediate.py,v 1.8 2009-12-14 11:45:32 poluekt Exp $
# =============================================================================
## @file  CommonParticles/StandardIntermediates.py
#  configuration file for 'Standard Intermediate particles
#  @author Patrick Koppenburg
#  @date 2009-02-18
# =============================================================================
"""
Configuration file for 'Standard Intermediate' particles
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.8 $"
# =============================================================================

_locations = {}

from CommonParticles.StandardV0 import *
_locations.update(locations)
from CommonParticles.StandardKstar import *
_locations.update(locations)
from CommonParticles.StandardRho import *
_locations.update(locations)
from CommonParticles.StandardPhi import *
_locations.update(locations)
from CommonParticles.StandardD0 import *
_locations.update(locations)
from CommonParticles.StandardDplus import *
_locations.update(locations)
from CommonParticles.StandardDstar import *
_locations.update(locations)
from CommonParticles.StandardJpsi import *
_locations.update(locations)
from CommonParticles.StandardDiMuon import *
_locations.update(locations)
from CommonParticles.StandardDiElectron import *
_locations.update(locations)
from CommonParticles.StandardLambdac import *
_locations.update(locations)
from CommonParticles.StandardTau import *
_locations.update(locations)
from CommonParticles.StandardTauNonPhys import *
_locations.update(locations)
from CommonParticles.StandardDipion import *
_locations.update(locations)
from CommonParticles.StandardLambdastar import *
_locations.update(locations)
from CommonParticles.StandardMuPi import *
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
