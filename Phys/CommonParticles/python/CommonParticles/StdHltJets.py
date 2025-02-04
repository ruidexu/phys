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
"""
Configuration file for 'StdHltJets'. Reconstructed jets produced by the HltJets algorithm.
"""
__author__ = "Carlos Vazquez Sierra"
__date__ = "25/04/2018"
__version__ = "v1r1"

# =============================================================================
__all__ = ('StdHltJets', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from CommonParticles.Utils import *

from Configurables import HltJetBuilder, HltParticleFlow, GaudiSequencer
from JetAccessories.HltJetConf import HltJetBuilderConf, HltParticleFlowConf
from GaudiKernel.SystemOfUnits import GeV

for jecs in [
    ['JECR05RUN2HLT', 'JetEnergyCorrections_R05_hlt_Run2.root'],
    ['JECRO5RUN2STD', 'JetEnergyCorrections_R05_std_Run2.root'],
    ['JECRO5RUN2TURBO', 'JetEnergyCorrections_R05_std_Turbo.root'],
]:
    hsvc = HistogramSvc('HistogramDataSvc')
    alreadySet = False
    for f in hsvc.Input:
        if f == "{0} DATAFILE='$PARAMFILESROOT/data/{1}' TYP='ROOT'".format(
                jecs[0], jecs[1]):
            alreadySet = True
    if not alreadySet:
        hsvc.Input += [
            "{0} DATAFILE='$PARAMFILESROOT/data/{1}' TYP='ROOT'".format(
                jecs[0], jecs[1])
        ]

ParticleFlow = HltParticleFlowConf('StdHltPF', SprRecover=True)
JetBuilder = HltJetBuilderConf(
    'StdHltJets',
    ParticleFlow.getOutputLocation(),
    JetEcPath='JECR05RUN2HLT',
    JetPtMin=5 * GeV,
    JetVrt=False)

algorithm = GaudiSequencer('StdHltJetsSeq')
algorithm.Members += [ParticleFlow.getSeq()]
algorithm.Members += [JetBuilder.getSeq()]

## configure Data-On-Demand service
locations = updateDoD(algorithm, name='StdHltJets')

## finally: define the symbol
StdHltJets = algorithm

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))

# =============================================================================
# The END
# =============================================================================
