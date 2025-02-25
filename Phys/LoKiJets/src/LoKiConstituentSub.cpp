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
// $Id: LoKiConstituentSub.cpp,v 1.1 2025-02-24 10:42:00 ruide Exp $
// ============================================================================
/** @file
 *  Implementation file for class LoKi::ConstituentSub
 *  @author Ruide Xu ruidexu@umich.edu, Ezra LESSER elesser@berkeley.edu 
 *  @date   2025-02-24
 */

#include "LoKiConstituentSub.h"
#include "LoKi/ILoKiSvc.h"  // for initializing class

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

  

  // How to treat massive particles
  if (keep_original_masses) { this->m_subtractor->set_keep_original_masses(); }
  if (fix_pseudorapidity)   { this->m_subtractor->set_fix_pseudorapidity(); }
  if (do_mass_subtraction)  { this->m_subtractor->set_do_mass_subtraction(); }
  if (scale_fourmomentum)   { this->m_subtractor->set_scale_fourmomentum(); }

  // Include any desired selectors
  sel_max_pt = fastjet::SelectorPtMax(this->m_max_pt_correct);

  this->m_subtractor->set_particle_selector(&sel_max_pt);

  // Initialize subtractor and print helpful info (if desired)
  this->m_subtractor->initialize();
  if (!(this->m_suppress_logging)) { std::cout << this->m_subtractor->description() << std::endl; }

  return StatusCode::SUCCESS;
}

StatusCode LoKi::ConstituentSub::subJets( IConstituentSubtractor::Input const &rawJets, IConstituentSubtractor::Output &subtractedJets ) const {

  // Trivial case of no particles in event
  if ( rawJets.empty() ) {
    subtractedJets = rawJets;
    if ( msgLevel( MSG::DEBUG ) && !(this->m_suppress_logging) ) { counter( "#jets" ) += rawJets.size(); }
    return StatusCode::SUCCESS;
  }

  // Estimate the background density (rho) for this event
  this->m_bge_rho.set_particles(rawJets);
  // Constituent Subtraction Routine
  std::vector<fastjet::PseudoJet> corrected_event = this->m_subtractor->subtract_event(rawJets);

  subtractedJets = corrected_event;

  if ( msgLevel( MSG::DEBUG ) && !(this->m_suppress_logging) ) { counter( "#jets" ) += subtractedJets.size(); }

  return StatusCode::SUCCESS;
}

// ============================================================================
// The factory
DECLARE_COMPONENT( LoKi::ConstituentSub )
// ============================================================================
