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
// $Id: IParticleDescendants.h,v 1.2 2009-08-04 09:45:31 jpalac Exp $
#ifndef KERNEL_IPARTICLEDESCENDANTS_H
#define KERNEL_IPARTICLEDESCENDANTS_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/IAlgTool.h"

/** @class IParticleDescendants IParticleDescendants.h Kernel/IParticleDescendants.h
 *
 *  Return the descendants of a Particle
 *
 *  @author Patrick KOPPENBURG
 *  @date   2005-10-19
 */
struct GAUDI_API IParticleDescendants : virtual public IAlgTool {

  DeclareInterfaceID( IParticleDescendants, 2, 0 );

  // Return all descendants of a Particle
  virtual const LHCb::Particle::ConstVector descendants( const LHCb::Particle* ) = 0;

  // Return all descendants of level i for a Particle
  virtual const LHCb::Particle::ConstVector descendants( const LHCb::Particle*, int ) = 0;

  // Return all stable descendants of a Particle
  virtual const LHCb::Particle::ConstVector finalStates( const LHCb::Particle* ) = 0;
};

#endif // KERNEL_IPARTICLEDESCENDANTS_H
