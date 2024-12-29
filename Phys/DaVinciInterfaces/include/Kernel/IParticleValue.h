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
#ifndef DAVINCIKERNEL_IPARTICLEVALUE_H
#define DAVINCIKERNEL_IPARTICLEVALUE_H 1
// ============================================================================
// Include files
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// Forward declarations
// ============================================================================
namespace LHCb {
  class Particle;
}
// ============================================================================
/** @class IParticleValue IParticleValue.h Kernel/IParticleValue.h
 *  Interface Class for Particle Values.
 *  Given an LHCb::Particle, return the value of a variable calculated from its properties
 *
 *  @author Sebastian Neubert
 *  @date   05/08/2013
 *
 */
struct GAUDI_API IParticleValue : extend_interfaces<IAlgTool> {
  // ==========================================================================
  DeclareInterfaceID( IParticleValue, 4, 0 );
  /// Value: Return false if particle does not pass filter.
  virtual double operator()( const LHCb::Particle* ) const = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // DAVINCIKERNEL_IPARTICLEVALUE_H
