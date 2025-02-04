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
// $Id: LoKiBackgroundSub.cpp,v 0.1 2024-01-24 14:18:00 elesser Exp $
// ============================================================================
/** @file
 *  Implementation file for class LoKi::ConstituentSub
 *  @author Ezra LESSER elesser@berkeley.edu Ruide Xu ruidexu@umich.edu
 *  @date   
 */

#include "LoKiConstituentSubtractor.h"

// ===========================================================================
// Standard initialization of the tool
StatusCode LoKi::ConstituentSub::initialize() {
  StatusCode sc = GaudiTool::initialize();
  if ( sc.isFailure() ) { return sc; }
  // Check the parameters
  sc = this->checkParams();
  if ( sc.isFailure() ) { return sc; }
  svc<LoKi::ILoKiSvc>( "LoKiSvc", true );
  if ( this->m_suppress_logging ) fastjet::ClusterSequence::set_fastjet_banner_stream( 0 );
  return sc;
}

// ===========================================================================
// Initialize the fastjet constituent subtractor using provided parameters
StatusCode LoKi::ConstituentSub::initializeSubtractor(
  const bool keep_original_masses /*= false*/, const bool fix_pseudorapidity /*= false*/,
  const bool do_mass_subtraction /*= false*/, const bool scale_fourmomentum /*= false*/) {

  // Set distance metric between particle i and ghost k
  if (this->m_distance_type) {
    // Euclidean angle between the momenta
    this->m_subtractor->set_distance_type(fastjet::contrib::ConstituentSubtractor::angle);
  } else {
    // Default distance metric (deltaR), where
    // deltaR = sqrt( (y_i-y_k)^2 + (phi_i-phi_k)^2 )
    this->m_subtractor->set_distance_type(fastjet::contrib::ConstituentSubtractor::deltaR);
  }
  this->m_subtractor->set_max_distance(this->m_max_distance);
  this->m_subtractor->set_alpha(this->m_alpha);
  this->m_subtractor->set_ghost_area(this->m_ghost_area);
  this->m_subtractor->set_max_eta(this->m_max_eta);
  this->m_subtractor->set_background_estimator((fastjet::BackgroundEstimatorBase*)(&m_bge_rho));
  //this->m_subtractor->set_background_estimator(m_bge_rho);
  

  // How to treat massive particles
  if (keep_original_masses) { this->m_subtractor->set_keep_original_masses(); }
  if (fix_pseudorapidity)   { this->m_subtractor->set_fix_pseudorapidity(); }
  if (do_mass_subtraction)  { this->m_subtractor->set_do_mass_subtraction(); }
  if (scale_fourmomentum)   { this->m_subtractor->set_scale_fourmomentum(); }

  // Include any desired selectors
  fastjet::Selector sel_max_pt = fastjet::SelectorPtMax(this->m_max_pt_correct);
  this->m_subtractor->set_particle_selector(&sel_max_pt);

  // Initialize subtractor and print helpful info (if desired)
  this->m_subtractor->initialize();
  if (!(this->m_suppress_logging)) { std::cout << this->m_subtractor->description() << std::endl; }

  return StatusCode::SUCCESS;
}


//|---> rdc <---| Not needed
// ===========================================================================
// Convert input object into a vector of fastjet::PseudoJet objects
/*StatusCode LoKi::ConstituentSub::prepareEvent(
  const IJetMaker::Input& input, std::vector<fastjet::PseudoJet>& full_event ) const {

  full_event.reserve( input.size() );
  for ( IJetMaker::Input::const_iterator ip = input.begin(); input.end() != ip; ++ip ) {
    const LHCb::Particle* p = *ip;
    if ( NULL == p ) {
      Warning( "Invalid input particle" ).ignore();
      continue;
    }
    full_event.push_back( this->makeJet( p, this->to_user_index( ip - input.begin() ) ) );
  }

  return StatusCode::SUCCESS;
}*/


//|---> rdc <---| Not needed
// ===========================================================================
// Process output "jets" into output particles
/*StatusCode LoKi::ConstituentSub::prepareOutput(
  const IJetMaker::Input& input, const std::vector<fastjet::PseudoJet>& corrected_event,
  IJetMaker::Jets& output ) const {

  output.reserve( corrected_event.size() );

  // Stand-in values for surviving ghost particles
  const int ghost_pid = 0;
  const LoKi::Point3D ghost_point = LoKi::Point3D( 0, 0, 0 );

  for ( const fastjet::PseudoJet & fjparticle : corrected_event ) {
    LHCb::Particle particle;

    // Save the particle PID and reference point from input particle
    const int index = this->from_user_index( fjparticle.user_index() );
    if ( index >= 0 ) {  // Saved from full_event
      // Find the appropriate input particle
      const LHCb::Particle* input_particle = input[index];
      particle.setParticleID( input_particle->particleID() );
      particle.setReferencePoint( input_particle->referencePoint() );
    } else {  // Probably a surviving ghost
      particle.setParticleID( LHCb::ParticleID( ghost_pid ) );
      particle.setReferencePoint( ghost_point );
    }

    // Save the corrected four-momentum
    particle.setMomentum( Gaudi::LorentzVector( fjparticle.px(), fjparticle.py(), fjparticle.pz(), fjparticle.e() ) );

    output.push_back( particle.clone() );
  }

  return StatusCode::SUCCESS;
}*/

//|---> rdc <---| Not needed
// ===========================================================================
// Process input particles into background-subtracked output particles (as "jets")
//StatusCode LoKi::ConstituentSub::makeJets(
   //const IJetMaker::Input& input, const LHCb::RecVertex& vtx, IJetMaker::Jets& jets_ ) const {

   //return this->makeJets( input, jets_ ).ignore( /* AUTOMATICALLY ADDED FOR gaudi/Gaudi!763 */ );
//}

// ===========================================================================
// Process input particles into background-subtracked output particles (as "jets")
///------>rdc<------ Made this function mutable, the set_partciles member is a non const function, cannot be called
StatusCode LoKi::ConstituentSub::subJets( const IConstituentSubtractor::Input& rawJets, IConstituentSubtractor::Output& subtractedJets ) {

  // First process particles from event into a vector of fastjet::PseudoJet objects
  //std::vector<fastjet::PseudoJet> full_event;
  //StatusCode sc = this->prepareEvent(rawJets, full_event);
  /*if ( sc.isFailure() ) {
    std::cerr << "Could not prepare event for Constituent Subtractor" << std::endl;
    return sc;
  }
  */

  // Trivial case of no particles in event
  if ( rawJets.empty() ) {
    subtractedJets = rawJets;
    if ( msgLevel( MSG::DEBUG ) && !(this->m_suppress_logging) ) { counter( "#jets" ) += rawJets.size(); }
    return StatusCode::SUCCESS;
  }

  // Estimate the background density (rho) for this event
  this->m_bge_rho.set_particles(rawJets);
  std::vector<fastjet::PseudoJet> corrected_event = this->m_subtractor->subtract_event(rawJets);

  // copy the corrected_event to subtracted Jets
  subtractedJets = corrected_event;

  // Copy corrected event into the proper output object
  /*IConstituentSubtractor::Output output{};
  sc = this->prepareOutput(rawJets, corrected_event, output);
  if ( sc.isFailure() ) {
    std::cerr << "Could not prepare output for Constituent Subtractor" << std::endl;
    return sc;
  }
  */

  if ( msgLevel( MSG::DEBUG ) && !(this->m_suppress_logging) ) { counter( "#jets" ) += subtractedJets.size(); }

  return StatusCode::SUCCESS;
}

// ============================================================================
// The factory
DECLARE_COMPONENT( LoKi::ConstituentSub )
// ============================================================================
