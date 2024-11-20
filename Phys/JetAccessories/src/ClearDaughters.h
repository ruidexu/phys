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
#ifndef CLEARDAUGHTERS_H
#define CLEARDAUGHTERS_H 1
// ============================================================================
// Include files
// DaVinci Kernel
// ============================================================================
#include "Kernel/DaVinciAlgorithm.h"
class ClearDaughters : public DaVinciAlgorithm {
protected:
  // ==========================================================================
  /// Base class type
  typedef DaVinciAlgorithm BaseClass;
  // ==========================================================================
public:
  // ==========================================================================
  /// the specific initialization
  StatusCode initialize() override; // the specific initialization
  /// the most interesting method
  StatusCode execute() override; // the most interesting method
  // finalize /reset functors
  StatusCode finalize() override;
  // ==========================================================================
  /** standard constructor
   *  @see DaVinciAlgorithm
   *  @see GaudiTupleAlg
   *  @see GaudiHistoAlg
   *  @see GaudiAlgorithm
   *  @see Algorithm
   *  @param name the algorithm instance name
   *  @param pSvc pointer to Service Locator
   */
  ClearDaughters                 // standard contructor
      ( const std::string& name, // the algorithm instance name
        ISvcLocator*       pSvc );     // pointer to Service Locator
  // ==========================================================================
protected:
  // ==========================================================================
  /// Get the related PV of particle and relate it to clone.
  void cloneP2PVRelation( const LHCb::Particle* particle, const LHCb::Particle* clone ) const;
  /// Write empty container if selection fails.
  void writeEmptyKeyedContainers() const;
  /// Write empty container if selection fails.
  void writeEmptySharedContainers() const;
  // ============================================================================
private:
  // ============================================================================
  /// save (clone if needed) selected particles in TES
  template <class PARTICLES, class VERTICES, class CLONER>
  StatusCode _save() const;
  // ============================================================================
protected:
  // ==========================================================================
  /// get the actual predicate:
  /// CloneFilteredParticles ?
  bool cloneFilteredParticles() const { return m_cloneFilteredParticles; }
  /// CloneFilteredParticles ?
  void setCloneFilteredParticles( const bool value ) { m_cloneFilteredParticles = value; }
  // ==========================================================================
  // ==========================================================================
private:
  // ==========================================================================
  /// save (clone if needed) selected particles in TES
  /// Success if number of saved particles == number saved
  /// to TES.
  /// Overwritten from DaVinciAlgorithm. Is called automatically.
  StatusCode _saveInTES() override;
  /// Write empty containers if selection fails.
  void writeEmptyTESContainers() override;
  // ==========================================================================
  // ==========================================================================
protected:
  // ==========================================================================
  /// CloneFilteredParticles ?
  bool m_cloneFilteredParticles; // CloneFilteredParticles ?
  // ==========================================================================
};
// ============================================================================

// ============================================================================
// The END
// ============================================================================
#endif // FILTERDESKTOP_H