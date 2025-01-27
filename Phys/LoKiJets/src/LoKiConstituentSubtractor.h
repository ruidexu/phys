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
// $Id: LoKiBackgroundSub.h,v 0.1 2024-01-24 14:18:00 elesser Exp $
// ============================================================================
/** @file
 *  Header file for class LoKi::ConstituentSub
 *  @author Ezra LESSER elesser@berkeley.edu Ruide Xu ruidexu@umich.edu
 *  @date   
 */

#ifndef LOKIBACKGROUNDSUB_H
#define LOKIBACKGROUNDSUB_H 1

// Gaudi
#include "GaudiAlg/GaudiTool.h"  // inherit properties from GaudiTool

// DaVinci kernel
#include "Kernel/IConstituentSubtractor.h"  // create PseudoJet object for each "particle"

// LoKi
#include "LoKi/ILoKiSvc.h"  // for initializing class
#include "LoKi/Geometry.h"  // for LoKi::Point3D

// Fastjet
#include "fastjet/ClusterSequence.hh"
#include "fastjet/Selector.hh"
//#include "fastjet/tools/BackgroundEstimatorBase.hh"
//#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"

namespace LoKi {
  /*
   * Constituent subtractor tool, as defined in 1403.3108
   *
   * Removes uncorrelated background in heavy-ion collisions
   * on a per-particle basis (useful for jet substructure)
   *
   * For a more detailed explanation of parameters, see
   * https://fastjet.fr/repo/doxygen-3.4.2/classfastjet_1_1GridMedianBackgroundEstimator.html
   * For an explanation of the boolean options, see
   * https://phab.hepforge.org/source/fastjetsvn/browse/contrib/contribs/ConstituentSubtractor/tags/1.4.6/example_event_wide.cc$57-77
   */

  //
  class ConstituentSub : public virtual IConstituentSubtractor, public GaudiTool {
    public:
      StatusCode subJets( const IConstituentSubtractor::Input& rawJets, IConstituentSubtractor::Output& subtractedJets) override;

      // Constructor
      ConstituentSub( const std::string& type, const std::string& name, const IInterface* parent )
        : GaudiTool( type, name, parent ),
          // Default background subtraction parameters
          m_max_distance( 0.3 ),
          m_alpha( 1 ),
          m_ghost_area( 0.01 ),
          m_max_eta( 6 ),
          m_bge_rho_grid_size( 0.2 ),
          m_max_pt_correct( 5 ),
          m_distance_type( 0 ),
          m_keep_original_masses( false ),
          m_fix_pseudorapidity( false ),
          m_do_mass_subtraction( false ),
          m_scale_fourmomentum( false ),
          m_suppress_logging( false ),
          m_bge_rho( m_max_eta , m_bge_rho_grid_size ) {

        // Set the background estimator to calculate background desnity (rho)
        // Options: GridMedianBackgroundEstimator or JetMedianBackgroundEstimator
        //   -- use former by default (TODO: implement choice of estimator)
        //this->m_bge_rho = new fastjet::GridMedianBackgroundEstimator( this->m_max_eta, this->m_bge_rho_grid_size );
        this->m_bge_rho= new fastjet::GridMedianBackgroundEstimator(this->m_max_eta, this->m_bge_rho_grid_size);

        // Initialize background subtractor
        this->m_subtractor = new fastjet::contrib::ConstituentSubtractor();
        StatusCode sc = this->initializeSubtractor(
          this->m_keep_original_masses, this->m_fix_pseudorapidity,
          this->m_do_mass_subtraction, this->m_scale_fourmomentum );
        //if ( sc.isFailure() ) { return sc; }

        declareInterface<IConstituentSubtractor>( this );
        declareProperty( "MaxDistance", m_max_distance, "Maximum allowed distance between particle i and ghost k" );
        declareProperty( "Alpha", m_alpha, "Free parameter for distance measure (exponent of pT)]" );
        declareProperty( "MaxEta", m_max_eta, "Maximum pseudorapidity for input particles to the subtraction" );
        declareProperty( "BgERhoGridSize", m_bge_rho_grid_size, "Requested grid spacing for grid-median background estimator" );
        declareProperty( "MaxPtCorrect", m_max_pt_correct, "Particles with pT > MaxPtCorrect will not be corrected" );
        declareProperty( "GhostArea", m_ghost_area, "Ghost 'area' (A_g) to set density of ghosts (smaller is better but slower)" );
        declareProperty( "SuppressLogging", m_suppress_logging, "Suppress standard output logging (useful for batch mode)" );
        declareProperty( "DistanceType", m_distance_type, "Type of distance measure between particle i and ghost k. Options: 0 (deltaR), 1 (angle)" );
      }

      // Destructor
      virtual ~ConstituentSub( ) {
        // Clean up virtual memory
        //delete m_bge_rho;
        delete m_subtractor;
      }

      // Standard initialization of the tool
      StatusCode initialize() override;

    private:
      double m_max_distance = -1;      // maximum allowed distance between particle i and ghost k
      double m_alpha = -1;             // free parameter for distance measure (exponent of pT)
      double m_ghost_area = 0;         // ghost "area" (A_g) to set density of ghosts (smaller is better but slower)
      double m_max_eta = -1;           // maximum pseudorapidity for input particles to the subtraction
      double m_bge_rho_grid_size = -1; // requested grid spacing for grid-median background estimator
      double m_max_pt_correct = -1;    // particles with pT above this value will not be corrected

      // type of distance between particle i and ghost k
      // Options: 0 (fastjet::contrib::ConstituentSubtractor::deltaR)
      //          1 (fastjet::contrib::ConstituentSubtractor::angle)
      int m_distance_type = -1;

      // mass handling settings
      bool m_keep_original_masses = false;
      bool m_fix_pseudorapidity = false;
      bool m_do_mass_subtraction = false;
      bool m_scale_fourmomentum = false;

      bool m_suppress_logging = false; // suppress standard output logging (useful for batch mode)


      // Check all of the parameters which should be initialized
      inline StatusCode checkParams() const {
        if ( m_max_distance < 0 || m_alpha < 0 || m_max_eta < 0 || m_bge_rho_grid_size < 0 ||
             m_max_pt_correct < 0 || m_ghost_area <= 0 || m_distance_type <= 0 ) {
          return Error( "Invalid input parameters specified" );
        }
        return StatusCode::SUCCESS;
      }

      //fastjet::GridMedianBackgroundEstimator* m_bge_rho = nullptr;  // Background estimator
      //fastjet::GridMedianBackgroundEstimator m_bge_rho = fastjet::GridMedianBackgroundEstimator( m_max_eta, m_bge_rho_grid_size );
      fastjet::contrib::ConstituentSubtractor* m_subtractor = nullptr;  // Background subtractor object


      // Initialize the fastjet constituent subtractor using provided parameters
      StatusCode initializeSubtractor(
        const bool keep_original_masses = false, const bool fix_pseudorapidity = false,
        const bool do_mass_subtraction = false, const bool scale_fourmomentum = false);

      //|---> rdc <---| Should I change these two lines in FastjetMaker?
      //|---> rdc <---| Should not be necessary if not doing data type conversion

      // Helper fuctions to adjust index values so that they are unaffected by other particles
      // (e.g. ghosts) which may or may not be created with conflicting user indices
      // in pb-pb event, there may be id over 10k.
      //int to_user_index( const int index ) const { return index + 1000000; }
      //int from_user_index( const int index ) const { return index - 1000000; }
      
      //|---> rdc <---| Not needed
      /*// Convert input object into a vector of fastjet::PseudoJet objects
      StatusCode prepareEvent(
        const IJetMaker::Input& input, std::vector<fastjet::PseudoJet>& full_event) const;*/
      // Process output "jets" into output particles
      /*StatusCode prepareOutput(
        const std::vector<const std::vector<fastjet::PseudoJet>& corrected_event,
        std::vector<fastjet::PseudoJet>& corrected_event output) const;
      */

      //|---> rdc <---| Not needed
      // Function which converts LHCb::Particle into fastjet::PseudoJet
      /*inline fastjet::PseudoJet makeJet( const LHCb::Particle* p, const int index ) const {
        if ( !p ) { return fastjet::PseudoJet(); }
        const Gaudi::LorentzVector& v = p->momentum();
        fastjet::PseudoJet jet( v.Px(), v.Py(), v.Pz(), v.E() );
        jet.set_user_index( index );
        return jet;
      }*/
  };
}

#endif
