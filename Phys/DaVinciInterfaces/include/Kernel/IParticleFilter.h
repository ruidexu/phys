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
#ifndef DAVINCIKERNEL_IPARTICLEFILTER_H
#define DAVINCIKERNEL_IPARTICLEFILTER_H 1
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
/** @class IParticleFilter IParticleFilter.h Kernel/IParticleFilter.h
 *  Interface Class for Particle Filters.
 *  Given an LHCb::Particle, return true if it passes the filter.
 *
 *  @author Juan Palacios
 *  @date   12/05/2010
 *
 */
struct GAUDI_API IParticleFilter : extend_interfaces<IAlgTool> {
  // ==========================================================================
  DeclareInterfaceID( IParticleFilter, 4, 0 );
  /// Filter: Return false if particle does not pass filter.
  virtual bool operator()( const LHCb::Particle* ) const = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // DAVINCIKERNEL_IPARTICLEFILTER_H
