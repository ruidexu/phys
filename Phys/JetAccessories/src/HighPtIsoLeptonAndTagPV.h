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
// ============================================================================
#ifndef HIGHPTISOLEPTONANDTAGPV_H
#define HIGHPTISOLEPTONANDTAGPV_H 1
// ============================================================================
// Include files
// ============================================================================
// from Gaudi
// ============================================================================
#include "GaudiAlg/GaudiTool.h"
#include "GaudiAlg/ITupleTool.h"
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// DaVinci Kernel
// ============================================================================
#include "Kernel/DaVinciAlgorithm.h"
#include "Kernel/IParticleCombiner.h"
// ============================================================================
// Event
// ============================================================================
#include "Event/Particle.h"
#include "GaudiKernel/IIncidentSvc.h"
//#include "Kernel/IContextTool.h"
#include "CaloDet/DeCalorimeter.h"
#include "Event/CaloDigit.h"
#include "Kernel/IParticleTransporter.h"
#include "Kernel/IVertexFit.h"
#include <Kernel/IDistanceCalculator.h>
//#include "Kernel/IGeomDispCalculator.h"
#include "MuonDAQ/IMuonRawBuffer.h"
// To recreate track measurements
#include "TrackInterfaces/IMeasurementProvider.h"

struct IDistanceCalculator;

class HighPtIsoLeptonAndTagPV : public DaVinciAlgorithm {
public:
  HighPtIsoLeptonAndTagPV( const std::string& name, ISvcLocator* pSvcLocator )
      : DaVinciAlgorithm( name, pSvcLocator )

      , m_FilterPart( true )
      , m_LeptID( 10099 )
      , m_niLeptID( 10199 )
      , m_LeptEJoverEL( 1.3 )
      , m_LeptRmax( 0.45 )
      , m_LeptMuPtTrackMin( 5000.0 )
      , m_LeptElPtTrackMin( 5000.0 )

      , m_LeptIPmax( 0.1 )
      , m_LeptSignif( 1. )

      , m_LeptjetMomRaw( false )
      , m_ipTool( 0 )
      , m_pVertexFit( 0 )

      , m_combinerName( "MomentumCombiner" )
      , m_combiner( 0 )

      , m_transporterName( "ParticleTransporter:PUBLIC" ) // The name of particle transpoter tool
      , m_transporter( 0 )

      , m_TrkChi2DoF( 2.5 )

  {

    declareProperty( "FilterPart", m_FilterPart );

    declareProperty( "IsoLeptID", m_LeptID, "Particle ID for the Lepton" );
    declareProperty( "NoIsoLeptID", m_niLeptID, "Particle ID for the Lepton" );

    declareProperty( "LeptEJoverEL", m_LeptEJoverEL );
    declareProperty( "LeptJetR", m_LeptRmax );
    declareProperty( "LeptMuPtTrackMin", m_LeptMuPtTrackMin );
    declareProperty( "LeptElPtTrackMin", m_LeptElPtTrackMin );
    declareProperty( "LeptIPmax", m_LeptIPmax );
    declareProperty( "LeptSignif", m_LeptSignif );
    declareProperty( "LeptJetRawEnergy", m_LeptjetMomRaw );
    declareProperty( "VertexFitter", m_typeVertexFit = "Default" );

    // define momentum combiner
    declareProperty( "ParticleCombiner", m_combinerName );

    declareProperty( "Transporter", m_transporterName, "The Particle Transporter tool to be used" );

    declareProperty( "SeedTrkChi2PerDoF", m_TrkChi2DoF, "max chi2PerDoF for the track used for the vtx" );
  }

  /** standard initialization of the tool
   *  @return status code
   */
  StatusCode initialize() override;

  StatusCode execute() override;

protected:
  /// make the detailed check of all parameters
  inline StatusCode check() const { return StatusCode::SUCCESS; }

protected:
  LHCb::Particle JetCone( const double&, Gaudi::XYZPoint, Gaudi::XYZPoint, const int&,
                          LHCb::Particle::ConstVector& ) const;

  StatusCode GetIsoLeptons( LHCb::Particle::ConstVector InLeptons, LHCb::Particle::ConstVector inputParts,
                            std::vector<LHCb::Particle>& Leptons, int& ) const;

  void RemoveTracks( LHCb::Particle::ConstVector& particles, const LHCb::RecVertex PV ) const;

protected:
  bool m_FilterPart;

  int m_LeptID;   ///< proposed jet ID
  int m_niLeptID; ///< proposed jet ID

  bool   m_useNN;
  double m_LeptEJoverEL;
  double m_LeptRmax;
  double m_LeptMuPtTrackMin;
  double m_LeptElPtTrackMin;

  double m_LeptIPmax;

  double m_LeptSignif;
  bool   m_LeptjetMomRaw;

  IMeasurementProvider*      m_measProvider;
  ITupleTool*                m_tuple;
  const IDistanceCalculator* m_ipTool;
  const IVertexFit*          m_pVertexFit;

  std::string                m_combinerName;
  mutable IParticleCombiner* m_combiner; ///< combiner to be used

  std::string m_transporterName;

  mutable IParticleTransporter* m_transporter;

  std::string m_geomToolName;
  std::string m_typeVertexFit;

  const IDistanceCalculator* distanceCalculator;

  const IDistanceCalculator* m_dist;

  double m_TrkChi2DoF;

  typedef LHCb::Relation1D<LHCb::Particle, LHCb::Particle> Table;
};

DECLARE_COMPONENT( HighPtIsoLeptonAndTagPV )
// ============================================================================
// The END
// ============================================================================
#endif // HIGHPTISOLEPTONANDTAGPV_H
