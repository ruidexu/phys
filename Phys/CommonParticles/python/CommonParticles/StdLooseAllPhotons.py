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
# $Id: StdLooseAllPhotons.py,v 1.2 2009-04-22 14:17:39 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StdLooseAllPhotons.py
#  configuration file for 'Standard Loose All Photons'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Loose All Photons'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.2 $"
# =============================================================================
__all__ = ('StdLooseAllPhotons', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import PhotonMakerAlg
from Configurables import PhotonMaker
from GaudiKernel.SystemOfUnits import MeV
from CommonParticles.Utils import *

## create the algorithm
algorithm = PhotonMakerAlg('StdLooseAllPhotons', DecayDescriptor='Gamma')

# configure desktop&particle maker:
algorithm.addTool(PhotonMaker, name='PhotonMaker')
photon = algorithm.PhotonMaker
photon.ConvertedPhotons = True
photon.UnconvertedPhotons = True
photon.PtCut = 200 * MeV

## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdLooseAllPhotons = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
