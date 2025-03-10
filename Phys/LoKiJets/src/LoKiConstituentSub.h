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
// $Id: LoKiConstituentSub.h,v 1.1 2025-02-24 10:42:00 ruide Exp $
// ============================================================================
/** @file
 *  Header file for class LoKi::ConstituentSub
 *  @author Ruide Xu ruidexu@umich.edu Ezra LESSER elesser@berkeley.edu 
 *  @date   2025-02-24
 */

#ifndef LOKICONSTITUENTSUB_H
#define LOKICONSTITUENTSUB_H 1
// ============================================================================
// Include files
// ============================================================================
// from Gaudi
// ============================================================================
#include "GaudiAlg/GaudiTool.h"  // inherit properties from GaudiTool
// ============================================================================
// DaVinci Kernel
// ============================================================================
#include "Kernel/IConstituentSubtractor.h"  // create PseudoJet object for each "particle"
// ============================================================================
// LoKi
// ============================================================================
#include "LoKi/Geometry.h"  // for LoKi::Point3D
// ============================================================================
// FastJet
// ============================================================================
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
      StatusCode subJets( IConstituentSubtractor::Input const &rawJets, IConstituentSubtractor::Output& subtractedJets) const override;

      // Constructor
      ConstituentSub( const std::string& type, const std::string& name, const IInterface* parent )
        : GaudiTool( type, name, parent ),
          // Default background subtraction parameters
          m_max_distance( 0.3 ),
          m_alpha( 1 ),
          m_ghost_area( 0.01 ),
          m_min_eta( 2 ),
          m_max_eta( 5 ),
          m_bge_rho_grid_size_rap( 0.2 ),
          m_bge_rho_grid_size_azm( 0.2 ),
          m_max_pt_correct( 5 ),
          m_distance_type( 0 ),
          m_keep_original_masses( false ),
          m_fix_pseudorapidity( false ),
          m_do_mass_subtraction( false ),
          m_scale_fourmomentum( false ),
          m_suppress_logging( false ) {

        // Set the background estimator to calculate background desnity (rho)
        // Options: GridMedianBackgroundEstimator or JetMedianBackgroundEstimator
        //   -- use former by default (TODO: implement choice of estimator)
        //this->m_bge_rho = new fastjet::GridMedianBackgroundEstimator( this->m_max_eta, this->m_bge_rho_grid_size );

        // Initialize background subtractor
        this->m_subtractor = new fastjet::contrib::ConstituentSubtractor();
        StatusCode sc = this->initializeSubtractor(
          this->m_keep_original_masses, this->m_fix_pseudorapidity,
          this->m_do_mass_subtraction, this->m_scale_fourmomentum );

        declareInterface<IConstituentSubtractor>( this );
        declareProperty( "CS_MaxDistance", m_max_distance, "Maximum allowed distance between particle i and ghost k" );
        declareProperty( "CS_Alpha", m_alpha, "Free parameter for distance measure (exponent of pT)]" );
        declareProperty( "CS_MinEta", m_min_eta, "Minimum pseudorapidity for input particles to the subtraction" );
        declareProperty( "CS_MaxEta", m_max_eta, "Maximum pseudorapidity for input particles to the subtraction" );
        declareProperty( "CS_BgERhoGridSize_rap", m_bge_rho_grid_size_rap, "Requested rapidity grid spacing for grid-median background estimator" );
        declareProperty( "CS_BgERhoGridSize_azm", m_bge_rho_grid_size_azm, "Requested azimuthal grid spacing for grid-median background estimator" );
        declareProperty( "CS_MaxPtCorrect", m_max_pt_correct, "Particles with pT > MaxPtCorrect will not be corrected" );
        declareProperty( "CS_GhostArea", m_ghost_area, "Ghost 'area' (A_g) to set density of ghosts (smaller is better but slower)" );
        declareProperty( "CS_SuppressLogging", m_suppress_logging, "Suppress standard output logging (useful for batch mode)" );
        declareProperty( "CS_DistanceType", m_distance_type, "Type of distance measure between particle i and ghost k. Options: 0 (deltaR), 1 (angle)" );
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
      double m_max_distance;      // maximum allowed distance between particle i and ghost k
      double m_alpha;             // free parameter for distance measure (exponent of pT)
      double m_ghost_area;         // ghost "area" (A_g) to set density of ghosts (smaller is better but slower)
      double m_min_eta;           // minimum pseudorapidity for input particles to the subtraction
      double m_max_eta;           // maximum pseudorapidity for input particles to the subtraction
      double m_bge_rho_grid_size_rap; // requested rapidity grid spacing for grid-median background estimator
      double m_bge_rho_grid_size_azm; // requested azimuthal grid spacing for grid-median background estimator
      double m_max_pt_correct;    // particles with pT above this value will not be corrected

      // type of distance between particle i and ghost k
      // Options: 0 (fastjet::contrib::ConstituentSubtractor::deltaR)
      //          1 (fastjet::contrib::ConstituentSubtractor::angle)
      int m_distance_type;

      // mass handling settings
      bool m_keep_original_masses;
      bool m_fix_pseudorapidity;
      bool m_do_mass_subtraction;
      bool m_scale_fourmomentum;

      bool m_suppress_logging; // suppress standard output logging (useful for batch mode)

      fastjet::Selector sel_max_pt;

      // Check all of the parameters which should be initialized
      inline StatusCode checkParams() const {
        if ( m_max_distance < 0 || m_alpha < 0 || m_min_eta < 0 || m_max_eta < 0 || m_bge_rho_grid_size_rap < 0 ||
             m_bge_rho_grid_size_azm < 0 ||m_max_pt_correct < 0 || m_ghost_area <= 0 || m_distance_type < 0 ) {
          return Error( "Invalid input parameters specified" );
        }
        return StatusCode::SUCCESS;
      }

      // Determines the area and the grid size for background mometum estimator
      mutable fastjet::GridMedianBackgroundEstimator m_bge_rho = fastjet::GridMedianBackgroundEstimator( m_min_eta, m_max_eta, m_bge_rho_grid_size_rap, m_bge_rho_grid_size_azm);
      fastjet::contrib::ConstituentSubtractor* m_subtractor = nullptr;  // Background subtractor object

      // Initialize the fastjet constituent subtractor using provided parameters
      StatusCode initializeSubtractor(
        const bool keep_original_masses = false, const bool fix_pseudorapidity = false,
        const bool do_mass_subtraction = false, const bool scale_fourmomentum = false);
  };
}

#endif
