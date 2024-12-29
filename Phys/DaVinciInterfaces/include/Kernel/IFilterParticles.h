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
#ifndef KERNEL_IFILTERPARTICLES_H
#define KERNEL_IFILTERPARTICLES_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

// Forward declarations
// from Event
#include "Event/Particle.h"

/** @class IFilterParticles IFilterParticles.h Kernel/IFilterParticles.h
 *
 *
 *  @author Juan Palacios
 *  @date   2007-07-20
 */
struct GAUDI_API IFilterParticles : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IFilterParticles, 2, 0 );

  /// Test if filter is satisfied on ensemble of particles
  virtual bool isSatisfied( const LHCb::Particle::ConstVector& parts ) const = 0;

  /// Test if filter is satisfied on ensemble of particles
  inline bool operator()( const LHCb::Particle::ConstVector& parts ) const { return this->isSatisfied( parts ); }
};

#endif // KERNEL_IFILTERPARTICLES_H
