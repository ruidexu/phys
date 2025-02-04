/*****************************************************************************\
* (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
// $Id: TupleToolPid.h,v 1.4 2010-03-04 14:02:03 xieyu Exp $
#ifndef JBOREL_TUPLETOOLPID_H
#define JBOREL_TUPLETOOLPID_H 1

// Include files
// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h" // Interface

/** @class TupleToolPid TupleToolPid.h
 *
 * @brief DLL and PID information to be stored in a Tuple
 *
 * \sa DecayTreeTuple
 *
 * - "head_ID" : "particle ID"
 * - "basic":
 *   - "head_PID{e,mu,K,p,d}" : "The combined delta log likelihood value for the electron/muon etc. hypothesis,
 * LHCb::ProtoParticle::CombDLLe"
 *   - "head_ProbNN{e,k,p,pi,mu,d,ghost}" : "The ANN probability for the electron/kaon etc. hypothesis,
 * LHCb::ProtoParticle::ProbNNe"
 *   - "head_hasMuon" : "track has hits consistent with a muon, LHCb::ProtoParticle::muonPID"
 *   - "head_isMuon" : "Is the track from a muon, LHCb::MuonPID::IsMuon"
 *   - "head_hasRich" : "RICH registered a track in event, LHCb::ProtoParticle::richPID"
 *   - "head_UsedRichAerogel" : "Aerogel was used to form this PID result, LHCb::RichPID::usedAerogel"
 *   - "head_UsedRich1Gas" : "Rich1 gas was used to form this PID result, LHCb::RichPID::usedRich1Gas"
 *   - "head_UsedRich2Gas" : "Rich2 gas was used to form this PID result, LHCb::RichPID::usedRich2Gas"
 *   - "head_RichAbove{El,Mu,Pi,Ka,Pr}Thres" : "Electron, Muon etc. Hypothesis over RICH threshold,
 * LHCb::RichPID::electronHypoAboveThres"
 *   - "head_hasCalo" : "hits in calorimeter, LHCb::ProtoParticle::calo"
 * - "Verbose":
 *   - "basic":
 *     - "head_RichDLL{e,mu,pi,k,p,bt,d}" : "delta log likelihood value for electron, muon, pion etc. hypothesis,
 * LHCb::ProtoParticle::RichDLLe"
 *     - "head_InAccMuon" : "Acceptance flag for MUON system (reaches geometrical acceptance),
 * LHCb::ProtoParticle::InAccMuon"
 *     - "head_isMuonLoose" : "muon candidates with the momentum between 3 and 6 GeV/c that have hits in at least M1-M4
 * muon stations and the candidates with the momentum greater than 6 GeV/c that have hits in all muon stations,
 * LHCb::MuonPID::IsMuonLoose"
 *     - "head_isMuonTight" : "only crossed hits, signal in x and y readout, LHCb::MuonPID::IsMuonTight"
 *     - "head_MuonNSharedHits" : "The number of muon system hits shared with other tracks, LHCb::MuonPID::nShared"
 *     - "head_MuonMuLL" : "The absolute value of the muon-like likelihood, LHCb::MuonPID::MuonLLMu"
 *     - "head_MuonBkgLL" : "The absolute value of the non-muon-like likelihood, LHCb::MuonPID::MuonLLBg"
 *     - "head_MuonChi2Correlated" : "The chi2 using the correlation of the hits, LHCb::MuonPID::Chi2Corr"
 *     - "head_InAccEcal" : "Flag in acceptance of Ecal-based CaloID, LHCb::ProtoParticle::InAccEcal"
 *     - "head_CaloEcalE" : "CaloID estimator : Ecal energy deposit (charged), LHCb::ProtoParticle::CaloEcalE"
 *     - "head_EcalPIDe" : "Ecal-based DLL for electron-ID, LHCb::ProtoParticle::EcalPIDe"
 *     - "head_EcalPIDmu" : "Ecal-based DLL for muon-ID DLL, LHCb::ProtoParticle::EcalPIDmu"
 *     - "head_InAccHcal" : "Flag in acceptance of Hcal-based CaloID, LHCb::ProtoParticle::InAccHcal"
 *     - "head_CaloHcalE" : "CaloID estimator : Hcal energy deposit (charged), LHCb::ProtoParticle::CaloHcalE"
 *     - "head_HcalPIDe" : "Hcal-based DLL for electron-ID, LHCb::ProtoParticle::HcalPIDe"
 *     - "head_HcalPIDmu" : "Ecal-based DLL for muon-ID DLL, LHCb::ProtoParticle::HcalPIDmu"
 *     - "head_InAccPrs" : "Flag in acceptance of Prs-based CaloID (PreShower), LHCb::ProtoParticle::InAccPrs"
 *     - "head_PrsPIDe" : "Prs-based DLL for electron-ID, LHCb::ProtoParticle::PrsPIDe"
 *     - "head_CaloPrsE" : "CaloID estimator : Prs energy deposit (charged), LHCb::ProtoParticle::CaloPrsE"
 *     - "head_InAccSpd" : "Flag in acceptance of Spd-based CaloID (Scintillating Pad), LHCb::ProtoParticle::InAccSpd"
 *     - "head_CaloSpdE" : "CaloID estimator : Spd hit, LHCb::ProtoParticle::CaloSpdE"
 *     - "head_InAccBrem" : "Flag in acceptance of Brem-based CaloID (Bremsstrahlung), LHCb::ProtoParticle::InAccBrem"
 *     - "head_BremPIDe" : "Brem-based DLL for electron-ID, LHCb::ProtoParticle::BremPIDe"
 *     - "head_VeloCharge" : "The dE/dx charge from the VELO system, LHCb::ProtoParticle::VeloCharge"
 *
 *  @author Jeremie Borel
 *  @date   2007-11-07
 *
 * Add more info:
 * -hasRich:  proto->richPID()!=0
 * -hasCalo:  proto->calo().size()>0
 * -hasMuon:  proto->muonPID()!=0
 * -isMuon:   proto->muonPID->IsMuon()
 *
 *  @date   2010-03-04
 */
class TupleToolPid : public TupleToolBase, virtual public IParticleTupleTool {

public:
  /// Standard constructor
  TupleToolPid( const std::string& type, const std::string& name, const IInterface* parent );

  virtual ~TupleToolPid(){}; ///< Destructor

  StatusCode fill( const LHCb::Particle*, const LHCb::Particle*, const std::string&, Tuples::Tuple& ) override;
};

#endif // JBOREL_TUPLETOOLPID_H
