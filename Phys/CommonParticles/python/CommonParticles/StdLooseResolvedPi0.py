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
# $Id: StdLooseResolvedPi0.py,v 1.3 2009-04-22 14:17:39 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StdLooseResolvedPi0.py
#  configuration file for 'Standard Loose Resolved Pi0s'
#  @author Patrick Koppenburg
#  @date 2009-02-18
# =============================================================================
"""
Configuration file for 'Standard Loose ResolvedPi0'
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.3 $"
# =============================================================================
__all__ = ('StdLoosePi02gg', 'StdLooseResolvedPi0', 'locations')
# =============================================================================
from GaudiKernel.SystemOfUnits import MeV
from CommonParticles.Utils import *

## create the algorithm
from Configurables import ResolvedPi0Maker, PhotonMaker
wide = ResolvedPi0Maker(
    'StdLoosePi02gg', DecayDescriptor='Pi0', MassWindow=60. * MeV)
wide.addTool(PhotonMaker)
wide.PhotonMaker.PtCut = 200. * MeV

## configure Data-On-Demand service
locations = updateDoD(wide)
## define the symbol:
StdLoosePi02gg = wide

# ============================================================================
## filter the ``standard''-mass window
from Configurables import FilterDesktop
fltr = FilterDesktop(
    'StdLooseResolvedPi0',
    Code="ADMASS('pi0') < 30 * MeV ",
    Inputs=['Phys/%s/Particles' % wide.name()])
## configure Data-On-Demand service
locations.update(updateDoD(fltr))
## finally: define the symbol
StdLooseResolvedPi0 = fltr

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
