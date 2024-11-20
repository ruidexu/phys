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
from __future__ import print_function
__version__ = "$Id: JetMaker_Config.py,v 1.1 2010-02-04 12:37:55 cocov Exp $"
__author__ = "Victor Coco <Victor.Coco@cern.ch>"
from builtins import object
from LHCbKernel.Configuration import *

from Configurables import (GaudiSequencer, LoKi__PFJetMaker,
                           LoKi__FastJetMaker, HistogramSvc)


class JetMakerConf(object):
    def __init__(
            self,
            _name,
            Inputs=['Phys/PFParticles/Particles'],
            #PFTypes = ['ChargedHadron','Muon','Electron','Photon','Pi0','HCALNeutrals','NeutralRecovery','V0','Charged0Momentum','ChargedInfMomentum','BadPhotonMatchingT','BadPhoton','IsolatedPhoton'],
            PFTypes=[
                'ChargedHadron', 'Muon', 'Electron', 'Photon', 'Pi0',
                'HCALNeutrals', 'NeutralRecovery', 'V0', 'Charged0Momentum',
                'BadPhoton', 'IsolatedPhoton'
            ],
            R=0.5,
            PtMin=5000.,
            AssociateWithPV=True,
            JetEnergyCorrection=True,
            JetIDCut=True,
            jetidnumber=98,
            onlySaveB=False,
            pvassociationMinIPChi2=True,
            algtype="anti-kt",
            listOfParticlesToBan=[]):

        jetname_dict = {"kt": 0, "Cambridge": 1, "anti-kt": 2}
        dictOfPFType = {
            'ChargedHadron': 2,
            'Muon': 3,
            'Electron': 4,
            'Photon': 11,
            'Pi0': 12,
            'MergedPi0': 13,
            'ResolvedPi0': 14,
            'HCALNeutrals': 15,
            'NeutralRecovery': 16,
            'V0': 101,
            'D': 102,
            'B': 103,
            'Charged0Momentum': 1001,
            'ChargedInfMomentum': 1002,
            'BadPhotonMatchingT': 1003,
            'BadPhoton': 1004,
            'IsolatedPhoton': 1005
        }
        self.name = _name
        self.Inputs = Inputs
        self.AssociateWithPV = AssociateWithPV
        self.R = R
        self.PtMin = PtMin
        self.JetEnergyCorrection = JetEnergyCorrection
        self.JetIDCut = JetIDCut
        self.jetMakerType = jetname_dict[algtype]
        self.jetidnumber = jetidnumber
        self.OnlySaveWithB = onlySaveB
        self.PVassociationMinIPChi2 = pvassociationMinIPChi2
        self.PFParticleTypes = [dictOfPFType[k] for k in PFTypes]
        if 'Pi0' in PFTypes:
            self.PFParticleTypes.append(dictOfPFType['MergedPi0'])
            self.PFParticleTypes.append(dictOfPFType['ResolvedPi0'])
        self.BanCandidates = listOfParticlesToBan
        self.algorithms = []
        ##self.JetSeq = GaudiSequencer( _name + 'Seq',IgnoreFilterPassed = True)
        self.setupJetMaker()
        hsvc = HistogramSvc('HistogramDataSvc')
        alreadySet = False
        if self.R == 0.5:
            for file in hsvc.Input:
                if file == "JEC14R05 DATAFILE='$PARAMFILESROOT/data/JetEnergyCorrections_R05_v3.root' TYP='ROOT'":
                    alreadySet = True
            if not alreadySet:
                hsvc.Input += [
                    "JEC14R05 DATAFILE='$PARAMFILESROOT/data/JetEnergyCorrections_R05_v3.root' TYP='ROOT'"
                ]
        elif self.R == 0.7:
            for file in hsvc.Input:
                if file == "JEC14R07 DATAFILE='$PARAMFILESROOT/data/JetEnergyCorrections_R07_v3.root' TYP='ROOT'":
                    alreadySet = True
            if not alreadySet:
                hsvc.Input += [
                    "JEC14R07 DATAFILE='$PARAMFILESROOT/data/JetEnergyCorrections_R07_v3.root' TYP='ROOT'"
                ]
        else:
            print(
                "WARNING R parameter is not supported by any official JEC. Make sure you manually set your correct JEC file"
            )

    def setupJetMaker(self):
        jetMakerName = self.name
        algo = LoKi__PFJetMaker(jetMakerName)
        algo.Associate2Vertex = self.AssociateWithPV
        algo.OnlySaveWithB = self.OnlySaveWithB
        algo.PVassociationMinIPChi2 = self.PVassociationMinIPChi2
        nametool = LoKi__FastJetMaker.__name__
        algo.addTool(LoKi__FastJetMaker, name=nametool)
        tool = getattr(algo, nametool)
        algo.JetMaker = tool.getTitleName()
        algo.Inputs = self.Inputs
        algo.BanCandidates = self.BanCandidates
        algo.PFParticleTypes = self.PFParticleTypes
        tool.Type = self.jetMakerType
        tool.RParameter = self.R
        tool.PtMin = self.PtMin
        tool.Recombination = 0
        tool.JetID = self.jetidnumber
        if self.JetEnergyCorrection:
            algo.ApplyJEC = True
            if self.R == 0.5:
                algo.HistoPath = 'JEC14R05/'
            elif self.R == 0.7:
                algo.HistoPath = 'JEC14R07/'
            else:
                print(
                    "WARNING R parameter is not supported by any official JEC. Make sure you manually set your correct JEC file"
                )
        if self.JetIDCut:
            algo.ApplyJetID = True

        ##self.JetSeq.Members+= [ algo  ]
        self.algorithms.append(algo)
