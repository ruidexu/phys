/*****************************************************************************\
* (c) Copyright 2000-2022 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
#include "TupleToolJetsBase.h"
#include "Kernel/IDVAlgorithm.h"
#include "Kernel/IDistanceCalculator.h"
#include "LoKi/AParticleCuts.h"
#include "LoKi/ParticleCuts.h"
#include <Kernel/GetIDVAlgorithm.h>

TupleToolJetsBase::TupleToolJetsBase( const std::string& type, const std::string& name, const IInterface* parent )
    : TupleToolBase( type, name, parent )
    , charge( LoKi::Cuts::ONE )
    , positiveParticles( LoKi::Cuts::ONE )
    , negativeParticles( LoKi::Cuts::ONE )
    , neutralParticles( LoKi::Cuts::ONE )
    , maxPT( LoKi::Cuts::ONE )
    , m_M( LoKi::Cuts::ONE )
    , m_MM( LoKi::Cuts::ONE )
    , m_dva( 0 )
    , m_dist( 0 ) {}
#define SAVEPOINT( POINT, FUN ) ( POINT ? POINT->FUN : -1.0 )
bool TupleToolJetsBase::WriteJetToTuple( const LHCb::Particle* jet, std::string prefix ) {
  // filter plus and minus signs out to the prefix
  std::map<std::string, std::string> replacements;
  replacements["+"] = "plus";
  replacements["-"] = "minus";
  for ( std::map<std::string, std::string>::iterator it = replacements.begin(); it != replacements.end(); ++it ) {
    size_t point = 0;
    while ( ( point = prefix.find( it->first ) ) != std::string::npos )
      prefix = prefix.replace( point, it->second.size(), it->second );
  }

  if ( msgLevel( MSG::DEBUG ) )
    debug() << ( jet ? "Filling jet object " : "Filling dummy jet object " ) << jet << " " << prefix
            << " in tuple at address " << m_tuple << endmsg;

  bool result = true;
  result &= ( *m_tuple )->column( prefix + "_PX", (double)( SAVEPOINT( jet, momentum().Px() ) ) );
  result &= ( *m_tuple )->column( prefix + "_PY", (double)( SAVEPOINT( jet, momentum().Py() ) ) );
  result &= ( *m_tuple )->column( prefix + "_PZ", (double)( SAVEPOINT( jet, momentum().Pz() ) ) );
  result &= ( *m_tuple )->column( prefix + "_PE", (double)( SAVEPOINT( jet, momentum().e() ) ) );
  result &= ( *m_tuple )->column( prefix + "_PT", (double)( SAVEPOINT( jet, momentum().Pt() ) ) );
  result &= ( *m_tuple )->column( prefix + "_P", (double)( SAVEPOINT( jet, momentum().P() ) ) );
  result &= ( *m_tuple )->column( prefix + "_Eta", (double)( SAVEPOINT( jet, momentum().Eta() ) ) );
  result &= ( *m_tuple )->column( prefix + "_Phi", (double)( SAVEPOINT( jet, momentum().Phi() ) ) );
  result &= ( *m_tuple )->column( prefix + "_M", (double)( SAVEPOINT( jet, momentum().mass() ) ) );

  result &= ( *m_tuple )->column( prefix + "_MLoKi", (double)( jet ? m_M( jet ) : -99.0 ) );
  result &= ( *m_tuple )->column( prefix + "_MMLoKi", (double)( jet ? m_MM( jet ) : -99.0 ) );
  result &= ( *m_tuple )->column( prefix + "_NTrk", (double)( jet->info( LHCb::JetIDInfo::Ntracks, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_N90", (double)( jet->info( LHCb::JetIDInfo::N90, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_MTF", (double)( jet->info( LHCb::JetIDInfo::MTF, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_NSatCells", (double)( jet->info( LHCb::JetIDInfo::NSatCalo, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_NHasPVInfo", (double)( jet->info( LHCb::JetIDInfo::NHasPV, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_JEC_Cor", (double)( jet->info( LHCb::JECInfo::JEC, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_JEC_PV", (double)( jet->info( LHCb::JECInfo::NPVsForJEC, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_JEC_Error", (double)( jet->info( LHCb::JECInfo::JECError, -999.9 ) ) );

  double weigth = 1.0;
  double myPT   = ( SAVEPOINT( jet, momentum().Pt() ) );

  if ( myPT < 20000 ) weigth = 1 - ( ( 20000 - myPT ) / 16000 );

  // weigth for 5GeV jet:

  result &= ( *m_tuple )->column( prefix + "_w", (double)( weigth ) );
  result &= ( *m_tuple )->column( prefix + "_CPF", (double)( jet->info( LHCb::JetIDInfo::CPF, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_JetWidth", (double)( jet->info( LHCb::JetIDInfo::JetWidth, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_NSatECAL", (double)( jet->info( LHCb::JetIDInfo::NSatECAL, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_NSatHCAL", (double)( jet->info( LHCb::JetIDInfo::NSatHCAL, -999.9 ) ) );
  result &=
      ( *m_tuple )->column( prefix + "_NIPChi2Inf4", (double)( jet->info( LHCb::JetIDInfo::NIPChi2Inf4, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfCharged", (double)( jet->info( LHCb::JetEnergyFractionInfo::Charged, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfChargedHadron",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::ChargedHadron, -999.9 ) ) );
  result &=
      ( *m_tuple )->column( prefix + "_EfMuon", (double)( jet->info( LHCb::JetEnergyFractionInfo::Muon, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfElectron", (double)( jet->info( LHCb::JetEnergyFractionInfo::Electron, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfNeutral", (double)( jet->info( LHCb::JetEnergyFractionInfo::Neutral, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfPhoton", (double)( jet->info( LHCb::JetEnergyFractionInfo::Photon, -999.9 ) ) );
  result &=
      ( *m_tuple )->column( prefix + "_EfPi0", (double)( jet->info( LHCb::JetEnergyFractionInfo::Pi0, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfMPi0", (double)( jet->info( LHCb::JetEnergyFractionInfo::MergedPi0, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfRPi0", (double)( jet->info( LHCb::JetEnergyFractionInfo::ResolvedPi0, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfNHad", (double)( jet->info( LHCb::JetEnergyFractionInfo::NeutralHadron, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfNReco",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::NeutralRecovery, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfCompo", (double)( jet->info( LHCb::JetEnergyFractionInfo::Composite, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_EfV0", (double)( jet->info( LHCb::JetEnergyFractionInfo::V0, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_EfD", (double)( jet->info( LHCb::JetEnergyFractionInfo::D, -999.9 ) ) );
  result &= ( *m_tuple )->column( prefix + "_EfB", (double)( jet->info( LHCb::JetEnergyFractionInfo::B, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfBadParticle",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::BadParticle, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfCharged0Momentum",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::Charged0Momentum, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfChargedInfMomentum",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::ChargedInfMomentum, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfBadPhotonMatchingT",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::BadPhotonMatchingT, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfBadPhoton", (double)( jet->info( LHCb::JetEnergyFractionInfo::BadPhoton, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfIsolatedPhoton",
                          (double)( jet->info( LHCb::JetEnergyFractionInfo::IsolatedPhoton, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_NLongTrk", (double)( jet->info( LHCb::JetEnergyFractionInfo::NLongTrk, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfLongTrk", (double)( jet->info( LHCb::JetEnergyFractionInfo::EfLongTrk, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_NDownTrk", (double)( jet->info( LHCb::JetEnergyFractionInfo::NDownTrk, -999.9 ) ) );
  result &=
      ( *m_tuple )
          ->column( prefix + "_EfDownTrk", (double)( jet->info( LHCb::JetEnergyFractionInfo::EfDownTrk, -999.9 ) ) );
  result &=
      ( *m_tuple )->column( prefix + "_NUpTrk", (double)( jet->info( LHCb::JetEnergyFractionInfo::NUpTrk, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_EfUpTrk", (double)( jet->info( LHCb::JetEnergyFractionInfo::EfUpTrk, -999.9 ) ) );

  result &= ( *m_tuple )->column( prefix + "_PU_NPVs", (double)( jet->info( LHCb::JetPileUpInfo::PUnPVs, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone06_SumPTLongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUSumPTLongTrkCone06, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone06_SumELongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUSumELongTrkCone06, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone06_NLongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUNLongTrkCone06, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone06_NUpVeloTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUNUpVeloTrkCone06, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone10_SumPTLongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUSumPTLongTrkCone10, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone10_SumELongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUSumELongTrkCone10, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone10_NLongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUNLongTrkCone10, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone10_NUpVeloTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUNUpVeloTrkCone10, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone15_SumPTLongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUSumPTLongTrkCone15, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone15_SumELongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUSumELongTrkCone15, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone15_NLongTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUNLongTrkCone15, -999.9 ) ) );
  result &= ( *m_tuple )
                ->column( prefix + "_PU_Cone15_NUpVeloTrk",
                          (double)( jet->info( LHCb::JetPileUpInfo::PUNUpVeloTrkCone15, -999.9 ) ) );

  if ( m_withJetConstituents == true ) {

    std::vector<const LHCb::Particle*>           constituentsvector = jet->daughtersVector();
    std::vector<const LHCb::Particle*>::iterator iconstituent       = constituentsvector.begin();
    std::vector<double>                          constituents_E;
    std::vector<double>                          constituents_pT;
    std::vector<double>                          constituents_pX;
    std::vector<double>                          constituents_pY;
    std::vector<double>                          constituents_pZ;
    std::vector<double>                          constituents_ID;
    std::vector<double>                          constituents_Eta;
    std::vector<double>                          constituents_Phi;
    std::vector<double>                          constituents_Q;
    std::vector<double>                          constituents_IP;
    std::vector<double>                          constituents_IPCHI2;
    std::vector<double>                          constituents_IPraw;
    std::vector<double>                          constituents_NNe;
    std::vector<double>                          constituents_NNk;
    std::vector<double>                          constituents_NNp;
    std::vector<double>                          constituents_NNpi;
    std::vector<double>                          constituents_NNmu;
    std::vector<double>                          constituents_Chi2;
    std::vector<double>                          constituents_QoverP;
    std::vector<double>                          constituents_trackX;
    std::vector<double>                          constituents_trackY;
    std::vector<double>                          constituents_trackZ;
    std::vector<double>                          constituents_trackVX;
    std::vector<double>                          constituents_trackVY;
    std::vector<double>                          constituents_trackVZ;
    std::vector<double>                          constituents_CaloNeutralEcal;
    std::vector<double>                          constituents_CaloNeutralHcal2Ecal;
    std::vector<double>                          constituents_CaloNeutralE49;
    std::vector<double>                          constituents_CaloNeutralPrs;

    const LHCb::VertexBase* BPV = m_dva->bestVertex( *iconstituent );

    double ip    = -100.0;
    int    zsign = 0;
    double ipC = 0, ipChi2 = 0, ipex = -100;
    double c, e;

    for ( ; iconstituent != constituentsvector.end(); ++iconstituent ) {
      const LHCb::Particle*      constituent = *iconstituent;
      const LHCb::ProtoParticle* proto       = constituent->proto();
      if ( charge( constituent ) != 0 ) {
        constituents_CaloNeutralEcal.push_back( -1000 );
        constituents_CaloNeutralHcal2Ecal.push_back( -1000 );
        constituents_CaloNeutralE49.push_back( -1000 );
        constituents_CaloNeutralPrs.push_back( -1000 );
        if ( proto ) {
          constituents_NNe.push_back( proto->info( LHCb::ProtoParticle::ProbNNe, -1000 ) );
          constituents_NNk.push_back( proto->info( LHCb::ProtoParticle::ProbNNk, -1000 ) );
          constituents_NNp.push_back( proto->info( LHCb::ProtoParticle::ProbNNp, -1000 ) );
          constituents_NNpi.push_back( proto->info( LHCb::ProtoParticle::ProbNNpi, -1000 ) );
          constituents_NNmu.push_back( proto->info( LHCb::ProtoParticle::ProbNNmu, -1000 ) );
          constituents_Chi2.push_back( proto->info( LHCb::ProtoParticle::TrackChi2PerDof, -1000 ) );
          const LHCb::Track* trk = proto->track();
          LHCb::State        sta = trk->firstState();
          c                      = std::abs( sta.qOverP() );
          e                      = sqrt( sta.errQOverP2() );
          constituents_QoverP.push_back( c / e );

          Gaudi::XYZPoint  Pos = trk->position();
          Gaudi::XYZVector Mom = trk->momentum();

          constituents_trackX.push_back( Pos.X() );
          constituents_trackY.push_back( Pos.Y() );
          constituents_trackZ.push_back( Pos.Z() );

          constituents_trackVX.push_back( Mom.X() );
          constituents_trackVY.push_back( Mom.Y() );
          constituents_trackVZ.push_back( Mom.Z() );

        } else {
          constituents_NNe.push_back( -1000 );
          constituents_NNk.push_back( -1000 );
          constituents_NNp.push_back( -1000 );
          constituents_NNpi.push_back( -1000 );
          constituents_NNmu.push_back( -1000 );
          constituents_Chi2.push_back( -1000 );
          constituents_QoverP.push_back( -1000 );

          constituents_trackX.push_back( -1000 );
          constituents_trackY.push_back( -1000 );
          constituents_trackZ.push_back( -1000 );

          constituents_trackVX.push_back( -1000 );
          constituents_trackVY.push_back( -1000 );
          constituents_trackVZ.push_back( -1000 );
        }

      } else {
        constituents_NNe.push_back( -1000 );
        constituents_NNk.push_back( -1000 );
        constituents_NNp.push_back( -1000 );
        constituents_NNpi.push_back( -1000 );
        constituents_NNmu.push_back( -1000 );
        constituents_Chi2.push_back( -1000 );
        constituents_QoverP.push_back( -1000 );

        constituents_trackX.push_back( -1000 );
        constituents_trackY.push_back( -1000 );
        constituents_trackZ.push_back( -1000 );

        constituents_trackVX.push_back( -1000 );
        constituents_trackVY.push_back( -1000 );
        constituents_trackVZ.push_back( -1000 );

        if ( proto ) {
          constituents_CaloNeutralEcal.push_back( proto->info( LHCb::ProtoParticle::CaloNeutralEcal, -1000 ) );
          constituents_CaloNeutralHcal2Ecal.push_back(
              proto->info( LHCb::ProtoParticle::CaloNeutralHcal2Ecal, -1000 ) );
          constituents_CaloNeutralE49.push_back( proto->info( LHCb::ProtoParticle::CaloNeutralE49, -1000 ) );
          constituents_CaloNeutralPrs.push_back( proto->info( LHCb::ProtoParticle::CaloNeutralPrs, -1000 ) );
        } else {
          constituents_CaloNeutralEcal.push_back( -1000 );
          constituents_CaloNeutralHcal2Ecal.push_back( -1000 );
          constituents_CaloNeutralE49.push_back( -1000 );
          constituents_CaloNeutralPrs.push_back( -1000 );
        }
      }

      constituents_E.push_back( constituent->momentum().E() );
      constituents_pT.push_back( constituent->momentum().Pt() );
      constituents_pX.push_back( constituent->momentum().Px() );
      constituents_pY.push_back( constituent->momentum().Py() );
      constituents_pZ.push_back( constituent->momentum().Pz() );
      constituents_Eta.push_back( constituent->momentum().Eta() );
      constituents_Phi.push_back( constituent->momentum().Phi() );
      constituents_Q.push_back( constituent ? charge( constituent ) : -1.0 );
      constituents_ID.push_back( constituent->particleID().pid() );
      ip                   = -100.0;
      zsign                = -999;
      ipC                  = 0;
      ipChi2               = 0;
      ipex                 = -100;
      StatusCode       sc2 = m_dist->distance( constituent, BPV, ipC, ipChi2 );
      Gaudi::XYZVector ipV;
      StatusCode       sc = m_dist->distance( constituent, BPV, ipV );
      if ( sc2 && ipChi2 != 0 ) {
        if ( sc ) zsign = ipV.z() > 0 ? 1 : -1;
        ip   = ipC * zsign;
        ipex = ip / ipChi2;
      }
      constituents_IP.push_back( ipex );
      constituents_IPCHI2.push_back( ipChi2 );
      constituents_IPraw.push_back( ip );
    }

    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_E", constituents_E.begin(), constituents_E.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_pT", constituents_pT.begin(), constituents_pT.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_ID", constituents_ID.begin(), constituents_ID.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_pX", constituents_pX.begin(), constituents_pX.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_pY", constituents_pY.begin(), constituents_pY.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_pZ", constituents_pZ.begin(), constituents_pZ.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_Eta", constituents_Eta.begin(), constituents_Eta.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_Phi", constituents_Phi.begin(), constituents_Phi.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_Q", constituents_Q.begin(), constituents_Q.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_IP", constituents_IP.begin(), constituents_IP.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_IPCHI2", constituents_IPCHI2.begin(), constituents_IPCHI2.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_IPraw", constituents_IPraw.begin(), constituents_IPraw.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_NNe", constituents_NNe.begin(), constituents_NNe.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_NNk", constituents_NNk.begin(), constituents_NNk.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_NNp", constituents_NNp.begin(), constituents_NNp.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_NNpi", constituents_NNpi.begin(), constituents_NNpi.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_NNmu", constituents_NNmu.begin(), constituents_NNmu.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_Chi2", constituents_Chi2.begin(), constituents_Chi2.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_QoverP", constituents_QoverP.begin(), constituents_QoverP.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_Chi2", constituents_Chi2.begin(), constituents_Chi2.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_trackX", constituents_trackX.begin(), constituents_trackX.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_trackY", constituents_trackY.begin(), constituents_trackY.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_trackZ", constituents_trackZ.begin(), constituents_trackZ.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_trackVX", constituents_trackVX.begin(), constituents_trackVX.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_trackVY", constituents_trackVY.begin(), constituents_trackVY.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_trackVZ", constituents_trackVZ.begin(), constituents_trackVZ.end(),
                            prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_CaloNeutralEcal", constituents_CaloNeutralEcal.begin(),
                            constituents_CaloNeutralEcal.end(), prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_CaloNeutralHcal2Ecal", constituents_CaloNeutralHcal2Ecal.begin(),
                            constituents_CaloNeutralHcal2Ecal.end(), prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_CaloNeutralE49", constituents_CaloNeutralE49.begin(),
                            constituents_CaloNeutralE49.end(), prefix + "_nConstituents", 100 );
    result &= ( *m_tuple )
                  ->farray( prefix + "_Constituents_CaloNeutralPrs", constituents_CaloNeutralPrs.begin(),
                            constituents_CaloNeutralPrs.end(), prefix + "_nConstituents", 100 );
  }

  return result;
}

StatusCode TupleToolJetsBase::initialize() {
  const StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc;
  // get LoKi objects
  charge            = LoKi::Cuts::SUMTREE( LoKi::Cuts::Q, LoKi::Cuts::ALL, 0.0 );
  positiveParticles = LoKi::Cuts::NINTREE( LoKi::Cuts::Q > 0 );
  negativeParticles = LoKi::Cuts::NINTREE( LoKi::Cuts::Q < 0 );
  neutralParticles  = LoKi::Cuts::NINTREE( LoKi::Cuts::Q == 0 );
  maxPT             = LoKi::Cuts::MAXTREE( LoKi::Cuts::PT, LoKi::Cuts::BASIC, -1 );
  m_M               = LoKi::Particles::Mass();
  m_MM              = LoKi::Particles::MeasuredMass();
  m_dva             = Gaudi::Utils::getIDVAlgorithm( contextSvc(), this );
  if ( 0 == m_dva ) return Error( "Couldn't get parent DVAlgorithm", StatusCode::FAILURE );
  // Get distance calculator
  m_dist = m_dva->distanceCalculator();
  if ( !m_dist ) { return Error( "Unable to retrieve the IDistanceCalculator tool", StatusCode::FAILURE ); }

  return sc;
}

double TupleToolJetsBase::MaxSumNPart( const LHCb::Particle* jet, unsigned int n, const LoKi::Types::Fun& fun,
                                       SmartRefVector<LHCb::Particle>* SortedDaughters ) {
  if ( SortedDaughters && SortedDaughters->size() )
    return LoKi::Cuts::ASUM( fun )(
        LHCb::Particle::ConstVector( SortedDaughters->begin(), SortedDaughters->begin() + n ) );
  SmartRefVector<LHCb::Particle> constituents;
  if ( !SortedDaughters ) SortedDaughters = &constituents;
  SortedDaughters->assign( jet->daughters().begin(), jet->daughters().end() );
  sort( SortedDaughters->begin(), SortedDaughters->end(),
        Comperator<const LHCb::Particle*, const LHCb::Particle*>( fun ) );
  return LoKi::Cuts::ASUM( fun )(
      LHCb::Particle::ConstVector( SortedDaughters->begin(), SortedDaughters->begin() + n ) );
}
