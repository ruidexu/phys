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

__version__ = "$Id: HltJetConf.py,v 1.0 2017-03-06$"
__author__ = "Stephen Farry <stephen.farry@cern.ch>"

from builtins import str
from builtins import object
import six

from LHCbKernel.Configuration import *

from Configurables import (GaudiSequencer, CellularAutomatonAlg,
                           CaloClusterCovarianceAlg, CaloClusterizationTool,
                           CaloPhotonMatch, PhotonMatchAlg,
                           ChargedProtoParticleMaker, DelegatingTrackSelector,
                           TrackSelector, LoKi__Hybrid__TrackSelector)

from CommonParticles import (StdLooseAllPhotons, StdLooseResolvedPi0,
                             StdLooseMergedPi0, StdLooseKs, StdLooseLambda)

from Configurables import PFlowProtoFilter

from Configurables import HltParticleFlow


class HltParticleFlowConf(object):
    def __init__(
            self,
            _name,
            _inputs=[
                'Photons',
                'ResolvedPi0s',
                'MergedPi0s',
                'Ks',
                'Lambda',
                'ChargedProtos',
                'NeutralProtos',  #'VeloProtos',
                'EcalClusters',
                'HcalClusters',
                'EcalMatch',
                'HcalMatch',
                'PrimaryVtxs'
            ],
            _turboInputs=['ChargedProtos',
                          'NeutralProtos'],  #'EcalMatch', 'HcalMatch'],
            useTurbo=False,
            isMC=False,
            isRun2=True,
            **kwargs):

        self.name = _name
        self.useTurbo = useTurbo
        self.isMC = isMC
        self.isRun2 = isRun2
        sprrecover = True
        if self.useTurbo: sprrecover = False

        #default parameters
        self.params = {
            'ProBestNames': ['mu+', 'e+', 'p+', 'K+', 'pi+'],
            'ProBestKeys': [701, 700, 704, 703, 702],
            'ProBestMins': [0.5, 0.5, 0.5, 0.5, 0.5],
            'SprPid': -22,
            'EcalBest': True,
            'SprRecover': sprrecover,
            'TrkLnErrMax': 10,
            'TrkUpErrMax': 10,
            'TrkDnErrMax': 10
        }

        #Function strings for Calo response in data
        if self.isRun2:
            if self.isMC == False:
                # ECAL energy electron response:
                self.params[
                    'EcalElcEStr'] = "(-1.84500e-01 )*exp(-1.70173e-04*x)+8.10771e-01"
                # ECAL energy charged hadron response:
                self.params[
                    'EcalHadEStr'] = "( 3.00834e-01 )*exp(-2.32541e-04*x)+3.49919e-01"
                # HCAL energy electron response:
                self.params[
                    'HcalElcEStr'] = "(-1.84500e-01 )*exp(-1.70173e-04*x)+8.10771e-01"
                # HCAL energy charged hadron :
                self.params[
                    'HcalHadEStr'] = "(1.72514e-01)*exp(-2.56450e-05*x)+6.11010e-01"
                # ECAL + HCAL energy electron response:
                self.params[
                    'EcalHcalElcEStr'] = "(-1.84500e-01 )*exp(-1.70173e-04*x)+8.10771e-01"
                # ECAL + HCAL energy charged hadron response:
                self.params[
                    'EcalHcalHadEStr'] = "( -2.15730e-01 +3.22409e-04*x +1.98637e-13*x*x)*exp(-2.16718e-04*x)+8.37867e-01"
                #Function strings for Calo response in MCdata
            else:
                # ECAL energy electron response:
                self.params[
                    'EcalElcEStr'] = "( -2.86166e-01 )*exp(-6.44601e-05*x)+1.00566e+00"
                # ECAL energy charged hadron response:
                self.params[
                    'EcalHadEStr'] = "( 1.49825e+00 )*exp(-4.16364e-04*x)+2.40328e-01"
                # HCAL energy electron response:
                self.params[
                    'HcalElcEStr'] = "( -2.86166e-01 )*exp(-6.44601e-05*x)+1.00566e+00"
                # HCAL energy charged hadron:
                self.params[
                    'HcalHadEStr'] = "(1.36066e-01)*exp(-1.69589e-05*x)+6.45822e-01"
                # ECAL + HCAL energy electron response:
                self.params[
                    'EcalHcalElcEStr'] = "( -2.86166e-01 )*exp(-6.44601e-05*x)+1.00566e+00"
                # ECAL + HCAL energy charged hadron response:
                self.params[
                    'EcalHcalHadEStr'] = "( -8.64325e-02 +3.03866e-05*x +7.45740e-14*x*x)*exp(-9.57188e-05*x)+7.85786e-01"
        # update with user settings
        self.params.update(**kwargs)

        #possible inputs
        self.prepared_inputs = {
            'Photons': ['Particle', 'particle', StdLooseAllPhotons],
            'ResolvedPi0s': ['Particle', 'particle', StdLooseResolvedPi0],
            'MergedPi0s': ['Particle', 'particle', StdLooseMergedPi0],
            'Ks': ['Particle', 'particle', StdLooseKs],
            'Lambda': ['Particle', 'particle', StdLooseLambda],
            'ChargedProtos': ['ProtoParticle', 'best', self._chargedprotos],
            'NeutralProtos': ['ProtoParticle', 'gamma', 'Rec/ProtoP/Neutrals'],
            'EcalClusters': ['CaloCluster', 'gamma', 'Rec/Calo/EcalClusters'],
            'HcalClusters': ['CaloCluster', 'pi0', self._hcalclusters],
            'EcalMatch': ['IClusTrTable2D', 'ecal', 'Rec/Calo/ClusterMatch'],
            'HcalMatch': ['IClusTrTable2D', 'hcal', self._hcaltrackmatch],
            'VeloProtos': ['ProtoParticle', 'best', self._veloprotos],
            'PrimaryVtxs': ['RecVertex', 'vertex', 'Rec/Vertex/Primary']
        }

        #inputs selected by user - order is important
        if self.useTurbo == False: self.inputs = _inputs
        else: self.inputs = _turboInputs
        self.seq = GaudiSequencer(
            _name + "ParticleFlowSeq", IgnoreFilterPassed=True)

        #initialise and configure
        self.pflow = HltParticleFlow(_name, **self.params)
        self.configure()

    ## Configure the pflow algorithm
    def configure(self):
        self.pflow.Output = "Rec/" + self.name + "/Particles"
        for key in self.inputs:
            if key in list(self.prepared_inputs.keys()):
                inputClass, inputType, loc = self.prepared_inputs[key]

                #for hcal cluster or matching call function to add to sequence and return loc
                if key == 'HcalMatch' or key == 'VeloProtos' or key == 'HcalClusters' or key == "ChargedProtos":
                    self.pflow.Inputs.append([inputClass, inputType, loc()])

                #for common particles add all locations found as separate inputs
                elif hasattr(loc, 'locations'):
                    for l in loc.locations:
                        #ignore long-downstream locations
                        if 'LD' not in l:
                            self.pflow.Inputs.append(
                                [inputClass, inputType, l])

                #if location given as string just add
                else:
                    self.pflow.Inputs.append([inputClass, inputType, loc])

            elif isinstance(key, list) and len(key) == 3:
                self.pflow.Inputs.append([key[0], key[1], key[2]])
            else:
                print("Cannot add input ", key, " to particle flow")
        self.seq.Members += [self.pflow]

    def _hcalclusters(self):
        ## Create Sequencer
        ## Call the cluster creation
        ## Unique names to avoid any conflicts
        ## Hcal must in name to set up I/O
        hcalClus = CellularAutomatonAlg('PFHcalClusterization')
        clusTool = hcalClus.addTool(CaloClusterizationTool,
                                    "PFCaloClusterization")
        hcalClus.Tool = "CaloClusterizationTool/PFCaloClusterization"
        hcalClus.OutputData = 'Rec/Calo/PFHcalClusters'
        clusTool.ETcut = 2500
        clusTool.withET = True

        self.seq.Members += [hcalClus]
        ## Get the covariance matrix
        clustCov = CaloClusterCovarianceAlg('PFHcalCov')
        clustCov.EnergyTags = ['2x2']
        clustCov.CovarianceParameters["Stochastic"] = [0.7]
        clustCov.CovarianceParameters["GainError"] = [0.1]
        clustCov.InputData = "Rec/Calo/PFHcalClusters"
        clustCov.OutputData = 'Rec/Calo/PFHcalClusters'
        self.seq.Members += [clustCov]
        return clustCov.OutputData

    def _hcaltrackmatch(self):
        ## Create Sequencer
        hcal2Track = PhotonMatchAlg("PFHcal2TrackMatching")
        hcal2Track.Calos = ["Rec/Calo/PFHcalClusters"]
        hcal2Track.Output = "Rec/Calo/PFHcalClusterMatch"
        hcal2Track.Filter = "Rec/Calo/InAccHcal"
        hcalmatch = hcal2Track.addTool(CaloPhotonMatch, "PFHcalMatch")
        hcal2Track.Tool = "CaloPhotonMatch/PFHcalMatch"
        hcal2Track.Threshold = "1000"
        hcalmatch.Calorimeter = "/dd/Structure/LHCb/DownstreamRegion/Hcal"
        hcalmatch.Tolerance = "60"
        hcalmatch.Extrapolator = "TrackRungeKuttaExtrapolator/Regular"
        self.seq.Members += [hcal2Track]
        return hcal2Track.Output

    def _veloprotos(self):
        vprotos = ChargedProtoParticleMaker("VeloProtoPMaker")
        vprotos.Inputs = ["Rec/Track/Best"]
        vprotos.Output = "Rec/ProtoP/VeloProtoPMaker"
        vprotos.addTool(DelegatingTrackSelector, name="TrackSelector")
        vprotos.TrackSelector.TrackTypes = ["Velo"]
        self.seq.Members += [vprotos]
        return vprotos.Output

    def _chargedprotos(self):
        UTID = PFlowProtoFilter("UTID")
        UTID.Input = "Rec/ProtoP/Charged"
        UTID.Output = "Rec/ProtoP/UniqueCharged"
        UTID.TrackSelectorType = "LoKi__Hybrid__TrackSelector"
        track_sel = UTID.addTool(
            LoKi__Hybrid__TrackSelector, name="TrackSelector")
        track_sel.Code = "   ((TrTYPE==3) & (sqrt(TrCOV2(4,4))*TrP<0.1))"
        track_sel.Code += " | ((TrTYPE==4) & (sqrt(TrCOV2(4,4))*TrP<0.5) & (TrCHI2PDOF<1.5) & (TrPT > 100.))"
        track_sel.Code += " | ((TrTYPE==5) & (sqrt(TrCOV2(4,4))*TrP<0.1) & (TrCHI2PDOF<1.5))"
        self.seq.Members += [UTID]
        return UTID.Output

    def getSeq(self):
        return self.seq

    def getOutputLocation(self):
        return self.pflow.Output


# ----------------------------------------------------------------------------------

from Configurables import HltJetBuilder, FilterDesktop


class HltJetBuilderConf(object):
    def __init__(self, _name, _inputs, jetid=True, **kwargs):

        self.params = {
            'JetR': 0.5,
            'JetPtMin': 5000.,
            'InputBans': [],
            'InputTags': [],
            'JetPid': 98,
            'JetVrt': False,
            'JetSort': 2,
            'JetInfo': True,
            'JetEcPath': "JEC1405",
            'JetEcShift': 0.0,
            'enableConstituentSubtractor': True
        }

        self.params.update(**kwargs)

        self.name = _name
        self.jetid = jetid
        if isinstance(_inputs, six.string_types):
            self.inputs = [_inputs]
        else:
            self.inputs = _inputs
        self.seq = GaudiSequencer(self.name + 'JetBuilderSeq')
        self._configure()

    def _configure(self):
        builder_name = self.name
        if self.jetid: builder_name += "_nojetid"
        self.jb = HltJetBuilder(builder_name, **self.params)
        self.jb.Inputs = self.inputs
        self.jb.Output = "Phys/" + builder_name + "/Particles"
        self.seq.Members += [self.jb]
        if self.jetid:
            jetfilter = FilterDesktop(self.name)
            jetfilter.Preambulo = [
                "import cppyy",
                "cppyy.gbl.gROOT.ProcessLine(\'#include \"Kernel/JetEnums.h\"\')"
            ]
            jetfilter.Inputs = ["Phys/" + builder_name + "/Particles"]
            jetfilter.Code = "(INFO(LHCb.JetIDInfo.CPF,-1) > 0.06) & (INFO(LHCb.JetIDInfo.MPT,-1)>1400) & (max(INFO(LHCb.JetIDInfo.MTF,-1),INFO(LHCb.JetIDInfo.MNF,-1))<0.75) & (INFO(LHCb.JetIDInfo.Ntracks,-1) > 1)"
            self.seq.Members += [jetfilter]

    def getSeq(self):
        return self.seq
