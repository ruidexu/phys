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
# $Id: StdLooseJpsi2ee.py,v 1.6 2010-05-21 09:53:29 pkoppenb Exp $
# =============================================================================
## @file  CommonParticles/StdLooseJpsi2ee.py
#  configuration file for 'Standard Loose Jpsi2ee'
#  @author Patrick Koppenburg
#  @date 2009-02-18
# =============================================================================
"""
Configuration file for 'Standard Loose Jpsi2ee'. Lieftime unbiased.
"""
__author__ = "Patrick Koppenburg"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.6 $"
# =============================================================================
__all__ = ('StdLooseJpsi2ee', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *

## ============================================================================
## create the algorithm
StdLooseJpsi2ee = CombineParticles('StdLooseJpsi2ee')
StdLooseJpsi2ee.Inputs = ["Phys/StdAllLooseElectrons/Particles"]
StdLooseJpsi2ee.DecayDescriptor = "J/psi(1S) -> e+ e-"

StdLooseJpsi2ee.CombinationCut = "(AM>2000*MeV) & (AM<3800*MeV) & (ADOCACHI2CUT(30,''))"
StdLooseJpsi2ee.MotherCut = "(VFASPF(VCHI2)<25)"

## configure Data-On-Demand service
locations = updateDoD(StdLooseJpsi2ee)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
