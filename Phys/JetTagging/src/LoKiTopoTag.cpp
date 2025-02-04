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
#include "LoKiTopoTag.h"

// ============================================================================
// Declaration of the Tool Factory
DECLARE_COMPONENT( LoKi::TopoTag )

// ============================================================================
// Standard Constructor
LoKi::TopoTag::TopoTag( const std::string& type, const std::string& name, const IInterface* parent )
    : GaudiTool( type, name, parent ), m_TriggerTisTosTool( 0 ) {
  // Interface
  declareInterface<IJetTagTool>( this );

  // Algorithm related properties
  declareProperty( "TriggerLine", m_TLine = "Hlt2Topo.*Body.*Decision" );

  return;
}

// ============================================================================
// Standard Initialization
StatusCode LoKi::TopoTag::initialize() {
  if ( msgLevel( MSG::VERBOSE ) ) verbose() << "Initialising algorithm" << endmsg;

  StatusCode sc = GaudiTool::initialize();
  if ( sc.isFailure() ) return sc;

  // svc<LoKi::ILoKiSvc>("LoKiSvc", true);

  m_TriggerTisTosTool = tool<ITriggerTisTos>( "TriggerTisTos", "TriggerTisTos", this );
  if ( m_TriggerTisTosTool == 0 ) return Error( "Couldn't get requested jet tag tool", StatusCode::SUCCESS );

  return sc;
}

// ============================================================================
// Standard Finalization
StatusCode LoKi::TopoTag::finalize() {
  if ( msgLevel( MSG::VERBOSE ) ) verbose() << "Finalising algorithm" << endmsg;

  return GaudiTool::finalize();
}

// ===========================================================================
// Calculate Tag Weight
bool LoKi::TopoTag::calculateJetProperty( const LHCb::Particle* jet, std::map<std::string, double>& jetWeight ) {

  ITriggerTisTos::TisTosDecision classifiedDec;
  m_TriggerTisTosTool->setOfflineInput( *jet );
  m_TriggerTisTosTool->setTriggerInput( "Hlt2Topo.*BBDT.*Decision" );
  classifiedDec = m_TriggerTisTosTool->triggerTisTos();

  double tag_global = 0;
  if ( classifiedDec.tos() == true ) tag_global = 1;

  // IT HAS TO BEHTE LAST ONE: GLOBAL DECISTION
  jetWeight["Tag"]       = tag_global;
  jetWeight["extraInfo"] = 5000;
  if ( msgLevel( MSG::DEBUG ) ) debug() << "Tag weight: " << jetWeight << endmsg;

  if ( tag_global )
    return true;
  else
    return false;
}
