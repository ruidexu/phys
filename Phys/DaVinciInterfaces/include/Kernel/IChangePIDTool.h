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
#ifndef KERNEL_ICHANGEPIDTOOL_H
#define KERNEL_ICHANGEPIDTOOL_H 1

// Include files
// from STL
#include <string>
#include <vector>

// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/IAlgTool.h"

/** @class IChangePIDTool IChangePIDTool.h Kernel/IChangePIDTool.h
 *
 *  Interface for ChangePIDTool.
 *  Changes the PID of a Particle or of every element of a list of Particles.
 *
 *  @author Patrick Spradlin
 *  @date   2006-12-13
 */
struct GAUDI_API IChangePIDTool : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IChangePIDTool, 2, 0 );

  /// Change the PID of a single particle
  virtual LHCb::Particle changePID( const LHCb::Particle& ) = 0;

  /// Change the PID of each member of a vector of particles
  virtual std::vector<LHCb::Particle> changePID( const LHCb::Particle::ConstVector& ) = 0;

  /// Templated findDecay method working on particle container iterators.
  template <class PARTICLE>
  inline std::vector<LHCb::Particle> changePID( PARTICLE begin, PARTICLE end ) {
    return changePID( {begin, end} );
  }
};
#endif // KERNEL_ICHANGEPIDTOOL_H
