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
#ifndef KERNEL_ISETINPUTPARTICLES_H
#define KERNEL_ISETINPUTPARTICLES_H 1
// ============================================================================
// Include files
// ============================================================================
// GaudiKernel
// ============================================================================
#include "GaudiKernel/IInterface.h"
// ============================================================================
// Event
// ============================================================================
#include "Event/Particle.h"
// ============================================================================
/** @class ISetInputParticles ISetInputParticles.h Kernel/ISetInputParticles.h
 *
 *  A bit technical interface to allow some interactive manipulations
 *  with CombineParticlesa algorithm form python.
 *
 *  @author Vanya BELYAEV Ivan.Belyaev@nikhef.nl
 *  @date   2008-07-11
 */
struct GAUDI_API ISetInputParticles : extend_interfaces<IInterface> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( ISetInputParticles, 2, 0 );
  // ==========================================================================
  /** the only one essential method:
   *  it sets the input particles
   *  @param input the vector of input particles
   *  @return status code
   */
  virtual StatusCode setInput( const LHCb::Particle::ConstVector& input ) = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // KERNEL_ISETINPUTPARTICLES_H
