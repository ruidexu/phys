###############################################################################
from __future__ import print_function
# (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
"""
Configuration file for Standard Loose Detached Kpi,
with Kpi invariant mass up to 2.2 GeV
"""

__author__ = 'Jibo He'
__date__ = '22/01/2012'

from Gaudi.Configuration import *
from Configurables import CombineParticles  # , OfflineVertexFitter, OnOfflineTool
from CommonParticles.Utils import *
import GaudiKernel.SystemOfUnits as Units

###########################
# StdDetachetKst2Kpi      #
###########################
StdLooseDetachedKpi = CombineParticles("StdLooseDetachedKpi")
StdLooseDetachedKpi.DecayDescriptor = "[K*(892)0 -> K+ pi-]cc"
StdLooseDetachedKpi.Inputs = [
    "Phys/StdLooseKaons/Particles", "Phys/StdLoosePions/Particles"
]

StdLooseDetachedKpi.CombinationCut = "(AM<2.2*GeV) & (ADOCACHI2CUT(30, ''))"
StdLooseDetachedKpi.MotherCut = "(VFASPF(VCHI2)<25)"

locations = updateDoD(StdLooseDetachedKpi)
