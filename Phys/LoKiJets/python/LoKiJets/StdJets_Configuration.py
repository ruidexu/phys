#!/usr/bin/env python
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
# $Id: StdJets_Configuration.py,v 1.1 2009-12-14 12:34:32 cocov Exp $
# =============================================================================
## @file  LoKiJets/StdJets.py
#  configuration file for 'Standard Jets made with FastJet'
#  @author Victor COCO victor.coco@cern.ch
#  @date 2009-09-09
# =============================================================================
"""
Configuration file for jets made with FastJet
"""
from __future__ import print_function
__author__ = "Victor COCO victor.coco@cern.ch"
__version__ = "v1r0"
# =============================================================================
__all__ = ('StdJets', 'FastJet', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import LoKi__JetMaker, LoKi__FastJetMaker
from CommonParticles.Utils import *

## create the algorithm
StdJets = LoKi__JetMaker('StdJets')

# select the jet maker
StdJets.JetMaker = 'LoKi__FastJetMaker'

StdJets.addTool(LoKi__FastJetMaker)

FastJet = getattr(StdJets, 'LoKi__FastJetMaker')

## configure Data-On-Demand service
locations = updateDoD(StdJets)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
