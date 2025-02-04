#!/usr/bin/env python
from __future__ import print_function
###############################################################################
# (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration           #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
"""
Configuration file for Standard Loose DiElectron, very loose for penguins
"""

__author__ = 'Patrick Koppenburg'
__date__ = '08/12/2009'

from Gaudi.Configuration import *
from Configurables import CombineParticles
from CommonParticles.Utils import *
import GaudiKernel.SystemOfUnits as Units

locations = {}

###########################
# StdLooseDiElectron #
###########################
"""
Standard Di-Electron maker from 2 electrons
"""
StdLooseDiElectron = CombineParticles("StdLooseDiElectron")
StdLooseDiElectron.DecayDescriptor = "J/psi(1S) -> e+ e-"
StdLooseDiElectron.Inputs = ["Phys/StdAllLooseElectrons/Particles"]
StdLooseDiElectron.DaughtersCuts = {"e+": "(PT>500*MeV)"}
StdLooseDiElectron.CombinationCut = "(AM>30*MeV) & (ADOCACHI2CUT(30,''))"
StdLooseDiElectron.MotherCut = "(VFASPF(VCHI2)<25)"
locations.update(updateDoD(StdLooseDiElectron))
"""
Using Olivier's Di-Electron Particle Maker
"""
###--- From Olivier's ParticleMaker
from Configurables import DiElectronMaker, ProtoParticleCALOFilter
from GaudiKernel.SystemOfUnits import *
dieLL = DiElectronMaker('StdDiElectronFromTracks')
dieLL.Particle = "J/psi(1S)"
selector = trackSelector(dieLL, trackTypes=["Long"])
dieLL.addTool(ProtoParticleCALOFilter, name='Electron')
dieLL.Electron.Selection = ["RequiresDet='CALO' CombDLL(e-pi)>'-2.0'"]
dieLL.DiElectronMassMax = 5000. * MeV
dieLL.DiElectronMassMin = 0. * MeV
dieLL.DiElectronPtMin = 200. * MeV
locations.update(updateDoD(dieLL))
StdDiElectronFromTracks = dieLL

# gamma version (clone)
StdDiElectronGamma = DiElectronMaker('StdDiElectronFromTracks').clone(
    "StdDiElectronGamma")
StdDiElectronGamma.Particle = "gamma"
locations.update(updateDoD(StdDiElectronGamma))

########################################################
# Addendum: M.v.Veghel, M. Mulder, C. Vazquez Sierra
# Clone from StdLooseDiElectron:
## Add the track type 'Upstream'
## No PID and CALO cuts on upstream, lower PT and add an IP chi2 cut.
########################################################
StdLooseDetachedDiElectronLU = CombineParticles("StdLooseDetachedDiElectronLU")
StdLooseDetachedDiElectronLU.DecayDescriptor = "J/psi(1S) -> e+ e-"
StdLooseDetachedDiElectronLU.Inputs = [
    "Phys/StdAllLooseElectrons/Particles",
    "Phys/StdNoPIDsUpElectrons/Particles"
]
StdLooseDetachedDiElectronLU.DaughtersCuts = {
    "e+": "(PT>250*MeV) & (MIPCHI2DV(PRIMARY) > 4)"
}
StdLooseDetachedDiElectronLU.CombinationCut = "(AM>30*MeV) & (ADOCACHI2CUT(30,''))"
StdLooseDetachedDiElectronLU.MotherCut = "(VFASPF(VCHI2)<25)"
locations.update(updateDoD(StdLooseDetachedDiElectronLU))

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
