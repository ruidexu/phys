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
# $Id: StdLooseElectrons.py,v 1.5 2010-06-01 09:41:12 odescham Exp $
# =============================================================================
## @file  CommonParticles/StdLooseElectrons.py
#  configuration file for 'Standard Loose Electrons'
#  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
#  @date 2009-01-14
# =============================================================================
"""
Configuration file for 'Standard Loose Electrons'
"""
__author__ = "Vanya BELYAEV Ivan.Belyaev@nikhef.nl"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.5 $"
# =============================================================================
__all__ = ('StdAllLooseElectrons', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import CombinedParticleMaker
from Configurables import ProtoParticleCALOFilter
from CommonParticles.Utils import *

## create the algorithm
algorithm = CombinedParticleMaker('StdAllLooseElectrons', Particle='electron')
# configure the track selector
selector = trackSelector(algorithm)
# protoparticle filter:
fltr = protoFilter(algorithm, ProtoParticleCALOFilter, 'Electron')
fltr.Selection = ["RequiresDet='CALO' CombDLL(e-pi)>'-2.0'"]
## configure Data-On-Demand service
locations = updateDoD(algorithm)

## finally: define the symbol
StdAllLooseElectrons = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
