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
# $Id: StdLooseKs.py,v 1.5 2009-05-26 13:48:13 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StdV0FromBrunel.py
#  configuration file for 'Standard Loose '
#  @author Patrick Koppenburg
#  @date 2012-06-08
# =============================================================================
"""
Configuration file for 'Standard Loose Ks'
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.5 $"
# =============================================================================
__all__ = ('V0Maker', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import DataOnDemandSvc, V0FromDstMaker
from CommonParticles.Utils import *
locations = {}

# One algorithm does all V0
v0locations = [
    "StdKs2PiPiLL", "StdKs2PiPiDD", "StdLambda2PPiLL", "StdLambda2PPiDD"
]
hat = "Phys/"
V0Maker = V0FromDstMaker()

dod = DataOnDemandSvc()

for v0 in v0locations:
    p1 = {hat + v0 + '/Particles': V0Maker.getFullName()}
    p2 = {hat + v0 + '/Particles': V0Maker}
    dod.AlgMap.update(p1)
    locations.update(p2)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
